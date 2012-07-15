require 'helper'

module GDA
  class TestNodes < TestCase
    attr_reader :parser

    def setup
      @parser = GDA::SQL::Parser.new
    end

    rails_sql.uniq.each do |sql|
      define_method(:"test_#{sql}") do
        stmt = parser.parse sql
        stmt.ast.each do |node|
          assert node
        end
      end
    end
  end
end

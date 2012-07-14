require 'minitest/autorun'
require 'gda'

module GDA
  module SQL
    class TestStatement < MiniTest::Unit::TestCase
      attr_reader :parser, :stmt

      def setup
        @parser = GDA::SQL::Parser.new
        @stmt = parser.parse 'SELECT * FROM FOO'
      end

      def test_serialize
        assert stmt.serialize
      end
    end
  end
end

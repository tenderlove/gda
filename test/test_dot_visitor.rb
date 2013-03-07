require 'helper'

module GDA
  class TestDotVisitor < TestCase
    attr_reader :parser

    class TestViz < Visitors::Dot
      def initialize tc
        super()
        @tc = tc
      end

      Visitors::Visitor.private_instance_methods.grep(/^visit_(.*)/) do |method|
        next if superclass.private_instance_methods(false).include?(method)

        klass = $1.split('_').inject(Object) { |k,c| k.const_get c }

        define_method(method) do |node|
          flunk "#{klass} (#{method}) not tested yet"
        end
      end

      def method_missing m, *args
        return super unless @tc.respond_to?(m)

        @tc.send m, *args
      end
    end

    def setup
      super
      @parser = GDA::SQL::Parser.new
      @viz    = TestViz.new(self)
    end

    rails_sql.uniq.each do |sql|
      define_method(:"test_#{sql}") do
        stmt = parser.parse sql
        @viz.accept stmt.ast
      end
    end
  end
end

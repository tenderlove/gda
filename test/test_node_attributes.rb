require 'helper'

module GDA
  class TestNodeAttributes < TestCase
    attr_reader :parser

    module Failing
    end

    class AttributeTest < Visitors::Visitor
      include Failing

      def initialize tc
        @tc = tc
      end

      private

      def visit_GDA_Nodes_Select node
        assert_respond_to node, :distinct?
        super
      end

      def visit_GDA_Nodes_Unknown node
        super
      end

      def visit_GDA_Nodes_Insert node
        assert_string node, :on_conflict
        super
      end

      def visit_GDA_Nodes_SelectField node
        [:field_name, :table_name, :as].each do |m|
          assert_string node, m
        end
        super
      end

      def visit_GDA_Nodes_Expr node
        assert_string node, :value
        assert_string node, :cast_as
        super
      end

      def visit_GDA_Nodes_Function node
        assert_string node, :function_name
        super
      end

      def visit_GDA_Nodes_From node
        super
      end

      def visit_GDA_Nodes_Table node
        assert_string node, :table_name
        super
      end

      def visit_GDA_Nodes_Update node
        assert_string node, :on_conflict
        super
      end

      def visit_GDA_Nodes_Operation node
        assert_string node, :operator
        super
      end

      def visit_GDA_Nodes_Field node
        assert_string node, :field_name
        super
      end

      def visit_GDA_Nodes_Join node
        assert_string node, :join_type
        assert_int node, :position
        super
      end

      def visit_GDA_Nodes_Target node
        assert_string node, :table_name
        assert_string node, :as
        super
      end

      def assert_string node, m
        assert_respond_to node, m
        assert_kind_of(String, node.send(m)) if node.send(m)
      end

      def assert_int node, m
        assert_respond_to node, m
        assert_kind_of(Numeric, node.send(m)) if node.send(m)
      end

      Visitors::Visitor.private_instance_methods.grep(/^visit_(.*)/) do |method|
        next if private_instance_methods(false).include?(method)

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
      @parser      = GDA::SQL::Parser.new
      @attr_tester = AttributeTest.new(self)
    end

    rails_sql.uniq.each do |sql|
      define_method(:"test_#{sql}") do
        stmt = parser.parse sql
        @attr_tester.accept stmt.ast
      end
    end
  end
end

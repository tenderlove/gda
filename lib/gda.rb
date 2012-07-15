require 'gda.so'

module GDA
  VERSION = '1.0.0'

  module Visitors
    class Visitor
      def accept node
        return unless node

        method = "visit_" + node.class.name.split('::').join('_')
        send method, node
      end

      private

      def visit_GDA_Nodes_Select node
        accept node.distinct_expr
        node.expr_list.each { |n| accept n }
        accept node.from
        accept node.where_cond
        node.group_by.each { |n| accept n }
        accept node.having_cond
        node.order_by.each { |n| accept n }
        accept node.limit_count
        accept node.limit_offset
      end

      def visit_GDA_Nodes_Insert node
        accept node.table
        node.fields_list.each { |n| accept n }
        accept node.select
      end

      def visit_GDA_Nodes_Update node
        accept node.table
        node.fields_list.each { |n| accept n }
        node.expr_list.each { |n| accept n }
        accept node.cond
      end

      def visit_GDA_Nodes_Join node
        accept node.expr
        node.use.each { |n| accept n }
      end

      def visit_GDA_Nodes_Delete node
        accept node.table
        accept node.cond
      end

      def visit_GDA_Nodes_SelectField node
        accept node.expr
      end

      def visit_GDA_Nodes_Expr node
        accept node.func
        accept node.cond
        accept node.select
        accept node.case_s
        accept node.param_spec
      end

      def visit_GDA_Nodes_From node
        node.targets.each { |n| accept n }
        node.joins.each { |n| accept n }
      end

      def visit_GDA_Nodes_Target node
        accept node.expr
      end

      def visit_GDA_Nodes_Operation node
        node.operands.each { |n| accept n }
      end

      def visit_GDA_Nodes_Function node
        node.args_list.each { |n| accept n }
      end

      def visit_GDA_Nodes_Order node
        accept node.expr
      end

      def visit_GDA_Nodes_Unknown node
        node.expressions.each { |n| accept n }
      end

      ## Terminal nodes
      def visit_GDA_Nodes_Table node
      end

      def visit_GDA_Nodes_Field node
      end

      def visit_GDA_Nodes_Savepoint node
      end

      def visit_GDA_Nodes_RollbackSavepoint node
      end
    end

    class Each < Visitor
      def initialize block
        @block = block
      end

      def accept node
        super
        @block.call node if node
      end
    end
  end

  module Nodes
    class Node
      def each &block
        Visitors::Each.new(block).accept self
      end
    end
  end
end

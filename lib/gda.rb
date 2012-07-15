require 'gda.so'

module GDA
  VERSION = '1.0.0'

  module Visitors
    class Visitor
      def accept node
        return unless node

        method = METHOD_CACHE.fetch(node.class) { |k|
          "visit_" + k.name.split('::').join('_')
        }

        send method, node
      end

      private

      def visit_Array node
        node.each { |n| accept n }
      end

      def visit_GDA_Nodes_Select node
        accept node.distinct_expr
        accept node.expr_list
        accept node.from
        accept node.where_cond
        accept node.group_by
        accept node.having_cond
        accept node.order_by
        accept node.limit_count
        accept node.limit_offset
      end

      def visit_GDA_Nodes_Insert node
        accept node.table
        accept node.fields_list
        accept node.values_list
        accept node.select
      end

      def visit_GDA_Nodes_Update node
        accept node.table
        accept node.fields_list
        accept node.expr_list
        accept node.cond
      end

      def visit_GDA_Nodes_Join node
        accept node.expr
        accept node.use
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
        accept node.targets
        accept node.joins
      end

      def visit_GDA_Nodes_Target node
        accept node.expr
      end

      def visit_GDA_Nodes_Operation node
        accept node.operands
      end

      def visit_GDA_Nodes_Function node
        accept node.args_list
      end

      def visit_GDA_Nodes_Order node
        accept node.expr
      end

      def visit_GDA_Nodes_Unknown node
        accept node.expressions
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

      def visit_GDA_Nodes_Begin node
      end

      def visit_GDA_Nodes_DeleteSavepoint node
      end

      def visit_GDA_Nodes_Rollback node
      end

      def visit_GDA_Nodes_Commit node
      end

      METHOD_CACHE = {}
      private_instance_methods.grep(/^visit_(.*)$/) do |method|
        k = $1.split('_').inject(Object) { |klass,c| klass.const_get c }
        METHOD_CACHE[k] = method
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

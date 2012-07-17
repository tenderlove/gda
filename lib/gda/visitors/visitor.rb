module GDA
  module Visitors
    class Visitor
      def accept node
        visit node
      end

      private

      def visit node
        return unless node

        method = METHOD_CACHE.fetch(node.class) { |k|
          "visit_" + k.name.split('::').join('_')
        }

        send method, node
      end

      def visit_Array node
        node.each { |n| visit n }
      end

      def visit_GDA_Nodes_Select node
        visit node.distinct_expr
        visit node.expr_list
        visit node.from
        visit node.where_cond
        visit node.group_by
        visit node.having_cond
        visit node.order_by
        visit node.limit_count
        visit node.limit_offset
      end

      def visit_GDA_Nodes_Insert node
        visit node.table
        visit node.fields_list
        visit node.values_list
        visit node.select
      end

      def visit_GDA_Nodes_Update node
        visit node.table
        visit node.fields_list
        visit node.expr_list
        visit node.cond
      end

      def visit_GDA_Nodes_Join node
        visit node.expr
        visit node.use
      end

      def visit_GDA_Nodes_Delete node
        visit node.table
        visit node.cond
      end

      def visit_GDA_Nodes_SelectField node
        visit node.expr
      end

      def visit_GDA_Nodes_Expr node
        visit node.func
        visit node.cond
        visit node.select
        visit node.case_s
        visit node.param_spec
      end

      def visit_GDA_Nodes_From node
        visit node.targets
        visit node.joins
      end

      def visit_GDA_Nodes_Target node
        visit node.expr
      end

      def visit_GDA_Nodes_Operation node
        visit node.operands
      end

      def visit_GDA_Nodes_Function node
        visit node.args_list
      end

      def visit_GDA_Nodes_Order node
        visit node.expr
      end

      def visit_GDA_Nodes_Unknown node
        visit node.expressions
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
  end
end

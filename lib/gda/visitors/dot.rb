require 'gda/visitors/visitor'
require 'erb'
require 'stringio'

module GDA
  module Visitors
    class Dot < GDA::Visitors::Visitor
      attr_reader :stack

      def initialize io = StringIO.new
        @stack  = []
        @buffer = io
      end

      def accept node
        puts "digraph G { graph [rankdir = \"TB\"];"
        super
        puts "}"
        @buffer.string
      end

      private

      def puts str
        @buffer.puts str
      end

      def printf *args
        @buffer.printf(*args)
      end

      NODE = ERB.new <<-eoerb
node<%= node.object_id %> [shape="plaintext" label=<
<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" CELLPADDING="4">
<TR><TD COLSPAN="2"><%= node.class %></TD></TR>
<% attrs.each do |attr| %>
  <% next if node.send(attr).nil? %>
  <TR><TD><%= attr %></TD><TD><%= node.send(attr) %></TD></TR>
<% end %>
</TABLE>>];
      eoerb

      LIST = ERB.new <<-eoerb
node<%= node.object_id %> [shape="invhouse", color=gray, fontcolor=gray, label=list];
      eoerb

      def add_node node, attrs = []
        puts NODE.result binding
        link_node node
      end

      def link_node node
        return if stack.empty?
        printf "node%d -> node%d [ label = \"%s\" ];\n", stack.last.first.object_id, node.object_id, stack.last.last
      end

      def add_list node
        puts LIST.result binding
        link_node node
      end

      def visit_edge node, edge
        stack.push [node, edge]
        visit node.send edge
        stack.pop
      end

      def visit_Array node
        return if node.empty?

        add_list node
        node.each_with_index { |n, i|
          stack.push [node, i]
          visit n
          stack.pop
        }
      end

      def visit_GDA_Nodes_Insert node
        add_node node, [:on_conflict]
        visit_edge node, :table
        visit_edge node, :fields_list
        visit_edge node, :values_list
      end

      def visit_GDA_Nodes_Update node
        add_node node, [:on_conflict]
        visit_edge node, :table
        visit_edge node, :fields_list
        visit_edge node, :expr_list
        visit_edge node, :cond
      end

      def visit_GDA_Nodes_Delete node
        add_node node
        visit_edge node, :table
        visit_edge node, :cond
      end

      def visit_GDA_Nodes_Select node
        add_node node
        visit_edge node, :distinct_expr
        visit_edge node, :expr_list
        visit_edge node, :from
        visit_edge node, :where_cond
        visit_edge node, :group_by
        visit_edge node, :having_cond
        visit_edge node, :order_by
        visit_edge node, :limit_count
        visit_edge node, :limit_offset
      end

      def visit_GDA_Nodes_Table node
        add_node node, [:table_name]
      end

      def visit_GDA_Nodes_SelectField node
        add_node node, [:field_name, :table_name, :as]
        visit_edge node, :expr
      end

      def visit_GDA_Nodes_Expr node
        add_node node, [:value, :cast_as]
        visit_edge node, :func
        visit_edge node, :cond
        visit_edge node, :select
        visit_edge node, :case_s
        visit_edge node, :param_spec
      end

      def visit_GDA_Nodes_Field node
        add_node node, [:field_name]
      end

      def visit_GDA_Nodes_Operation node
        add_node node, [:operator]
        visit_edge node, :operands
      end

      def visit_GDA_Nodes_From node
        add_node  node
        visit_edge node, :targets
        visit_edge node, :joins
      end

      def visit_GDA_Nodes_Target node
        add_node  node, [:table_name, :as]
        visit_edge node, :expr
      end

      def visit_GDA_Nodes_Function node
        add_node  node, [:function_name]
        visit_edge node, :args_list
      end

      def visit_GDA_Nodes_Order node
        add_node  node, [:asc, :collation_name]
        visit_edge node, :expr
      end

      def visit_GDA_Nodes_Unknown node
        add_node  node
        visit_edge node, :expressions
      end

      def visit_GDA_Nodes_Join node
        add_node node, [:join_type, :position]
        visit_edge node, :expr
        visit_edge node, :use
      end

      def visit_GDA_Nodes_Savepoint node
        add_node node, [:__type__, :isolation_level, :trans_mode, :trans_name]
      end

      alias visit_GDA_Nodes_RollbackSavepoint visit_GDA_Nodes_Savepoint
      alias visit_GDA_Nodes_DeleteSavepoint   visit_GDA_Nodes_Savepoint
      alias visit_GDA_Nodes_Rollback          visit_GDA_Nodes_Savepoint
      alias visit_GDA_Nodes_Commit            visit_GDA_Nodes_Savepoint
      alias visit_GDA_Nodes_Begin             visit_GDA_Nodes_Savepoint
    end
  end
end

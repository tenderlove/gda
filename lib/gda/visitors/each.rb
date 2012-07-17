require 'gda/visitors/visitor'

module GDA
  module Visitors
    class Each < Visitor
      def initialize block
        @block = block
      end

      def accept node
        super
        unless node.nil? || Array === node
          @block.call node
        end
      end
    end
  end
end

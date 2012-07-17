require 'gda/visitors/visitor'

module GDA
  module Visitors
    class MaxDepth < Visitor
      def initialize
        @max     = 0
        @current = 0
        super
      end

      def accept node
        super
        @max
      end

      private

      def visit node
        return super if node.nil?

        @current += 1
        super
        @max = [@max, @current].max
        @current -= 1
      end
    end
  end
end

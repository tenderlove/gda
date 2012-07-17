require 'gda.so'
require 'gda/visitors/each'
require 'gda/visitors/dot'
require 'gda/visitors/max_depth'

module GDA
  VERSION = '1.0.0'

  module Nodes
    class Node
      include Enumerable

      def each &block
        Visitors::Each.new(block).accept self
      end

      def to_dot
        viz = Visitors::Dot.new
        viz.accept self
      end

      def max_depth
        Visitors::MaxDepth.new.accept(self)
      end
    end
  end
end

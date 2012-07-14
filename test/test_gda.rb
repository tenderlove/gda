require 'minitest/autorun'
require 'gda'

class TestGda < MiniTest::Unit::TestCase
  def test_sanity
    parser = GDA::Parser.new
  end
end

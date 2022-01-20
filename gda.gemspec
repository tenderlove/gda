# frozen_string_literal: true

require_relative 'lib/gda/version'

Gem::Specification.new do |spec|
  spec.name = "gda"
  spec.version = GDA::VERSION

  spec.required_rubygems_version = Gem::Requirement.new(">= 2.5.0")
  spec.require_paths = ["lib"]
  spec.authors = ["Aaron Patterson"]
  spec.date = "2019-03-20"
  spec.description = "An SQL parser. Wraps libgda in a loving embrace to give you a ruby level SQL\nparser."
  spec.email = ["tenderlove@ruby-lang.org"]
  spec.extensions = ["ext/gda/extconf.rb"]
  spec.extra_rdoc_files = ["CHANGELOG.rdoc", "Manifest.txt", "README.rdoc", "CHANGELOG.rdoc", "README.rdoc"]
  spec.files = Dir.chdir(File.expand_path('..', __FILE__)) do
    Dir['{lib,ext}/**/*'].reject { |f| f =~ /\.(bundle|so|dll)/} +
      %w(LICENSE.txt README.md)
  end
  spec.homepage = "http://github.com/tenderlove/gda"
  spec.licenses = ["MIT"]
  spec.rdoc_options = ["--main", "README.rdoc"]
  spec.required_ruby_version = Gem::Requirement.new(">= 2.5.0")
  spec.summary = "An SQL parser"
end

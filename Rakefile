# frozen_string_literal: true
require "bundler/gem_tasks"
require "rake/testtask"

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList["test/**/test_*.rb"]
end

require "rake/extensiontask"

Rake::ExtensionTask.new("gda") do |ext|
  ext.ext_dir = 'ext/gda'
  ext.lib_dir = "lib/gda"
end

task default: %i(compile test)

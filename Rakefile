require 'rake/clean'

all     = FileList['sls/**/*.cpp', 'sls/**/*.hpp']
sources = FileList['sls/**/*.cpp']
objects = sources.ext('.o').gsub /^/, "../obj/"
paths   = sources.pathmap "%d"

CLEAN.include '../obj'


task :default => [ :fast ]

###############################################################################
######## build rules ##########################################################
###############################################################################
working_dir   = ""
build_cmd     = ""
link_cmd      = ""

#### dump build params ########################################################
task :dump_params do
  puts ""
  puts "### paramaters set..."
  puts "working directory : #{working_dir}"
  puts "build cmd         : #{build_cmd}"
  puts "link cmd          : #{link_cmd}"
  puts ""
end

#### obj dirs #################################################################
task :obj_dirs => [ :clean ] do
  sh "mkdir -p ../obj"

  paths.each do |path|
    sh "mkdir -p ../obj/#{path}"
  end
end

#### generic compile rule #####################################################
rule( /\.\.\/obj\/(\w+\/)*\w+\.o/ => [
    proc {|task_name| task_name.gsub("../obj/", "").gsub(".o", ".cpp") }
  ]) do |t|
  sh "/usr/local/bin/g++ -c #{build_cmd} -std=c++11 -o #{t.name} #{t.source}"
end

#### generic link rule ########################################################
rule( /\.\.\/\w+\/ssa/ => objects) do |t|
  sh "/usr/local/bin/g++ #{link_cmd} -o #{t.name} #{objects}"
  sh "cp #{working_dir}/ssa ../working/ssa"
  sh "cp #{working_dir}/ssa ../working-maxsat/ssa"
end

#### release ##################################################################
task :release => [ :release_params, :dump_params, :obj_dirs, "../release/ssa" ]

task :release_params do
  working_dir   = "../release"
  build_cmd     = "-O3"
  link_cmd      = "-O3"

  sh "mkdir -p #{working_dir}"
end

#### debug ####################################################################
task :debug => [ :debug_params, :dump_params, :obj_dirs, "../debug/ssa" ]

task :debug_params do
  working_dir   = "../debug"
  build_cmd     = "-O0 -Wall -Wextra"
  link_cmd      = "-O0 -Wall -Wextra"

  sh "mkdir -p #{working_dir}"
end

#### profile ##################################################################
task :profile => [ :profile_params, :dump_params, :obj_dirs, "../profile/ssa" ]

task :profile_params do
  working_dir   = "../profile"
  build_cmd     = "-O1 -g -pg"
  link_cmd      = "-O1 -pg"

  sh "mkdir -p #{working_dir}"
end

#### fast #####################################################################
task :fast => [ :fast_params, :dump_params, :obj_dirs, "../fast/ssa" ]

task :fast_params do
  working_dir   = "../fast"
  build_cmd     = "-O0 -ftrapv -fwrapv"
  link_cmd      = "-O0"

  sh "mkdir -p #{working_dir}"
end

#### pgo_gen ##################################################################
task :pgo_gen => [ :pgo_gen_params, :dump_params, :obj_dirs, "../pgo_gen/ssa" ]

task :pgo_gen_params do
  working_dir   = "../pgo_gen"
  build_cmd     = "-O3 -flto -fwhole-program -fprofile-generate -fprofile-arcs"
  link_cmd      = "-O3 -flto -fprofile-generate -fprofile-arcs"

  sh "mkdir -p #{working_dir}"
end

#### pgo_use ##################################################################
task :pgo_use => [ :pgo_use_params, :dump_params, :obj_dirs, "../pgo_use/ssa" ]

task :pgo_use_params do
  working_dir   = "../pgo_use"
  build_cmd     = "-O3 -flto -fwhole-program -fprofile-use"
  link_cmd      = "-O3 -flto -fprofile-use"

  sh "mkdir -p #{working_dir}"
end


###############################################################################
######## export rules #########################################################
###############################################################################

#### archive ##################################################################
task :archive => [ "ssa.tar" ]

file "ssa.tar" => all do
  sh "tar -cz sls > ssa.tar"
end

#### backup ###################################################################
task :backup => [ :archive ] do
  sh "scp ssa.tar spock:ssa/ssa-#{Time.now.strftime "%Y-%m-%d_%H:%M"}.tar"
end

#### timed backup #############################################################
task :timed_backup do
  if not File.exists? "ssa.tar" or Time.now - (File.atime "ssa.tar") > 3600
    sh "tar -cz sls > ssa.tar"
    sh "scp ssa.tar spock:ssa/ssa-#{Time.now.strftime "%Y-%m-%d_%H:%M"}.tar"
  end
end

#### atlas ####################################################################
task :atlas do
  sh "rm -f ssa.tar"
  sh "tar -cz sls > ssa.tar"
  sh "scp ssa.tar atlas:ssa/"
  sh "ssh atlas \"cd ssa; ./build.rb\""
end


###############################################################################
######## utility rules ########################################################
###############################################################################

#### todo #####################################################################
task :todo do
  sh "grep -r \"TODO\" sls"
end

#### git ######################################################################
task :commit do
  sh "git commit -a -m \"auto commit\""
end


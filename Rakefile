$buildnumber = $buildnumber  ? $buildnumber : ENV['BUILD_NUMBER'].nil? ? Time.now.strftime("%Y_%m_%d_%H_%M_%S") : ENV['BUILD_NUMBER']

require "rubygems"
require 'json'

task :default => [:new_build]

desc "Create dev"
task :dev_create => [:set_dev_env,:new_build] do
end

desc "Update dev"
task :dev_update => [:set_dev_env, :configure, :drupal_custom_modules_deploy] do
end

desc "Remove dev"
task :dev_remove => [:set_dev_env, :configure] do
  system "rm -R #{VerstakConf::BUILD_BASE_DIR}"

  system "mysql"+
             " --user=#{VerstakConf::MYSQL_USER}"+
             " --password=#{VerstakConf::MYSQL_PASS}"+
             " -e \"DROP DATABASE IF EXISTS #{VerstakConf::MYSQL_DBNAME}\""
end

desc "Create and deploy snapshot to presentation"
task :new_build => [
    :configure,
    :diagnostic,
    :deploy_build,
    :install_drupal,
    :drupal_modules_download,
    :drupal_modules_enable,
    :drupal_scripts_run
] do
end


task :set_dev_env do
    ENV['BUILD_NUMBER'] = 'dev'
end

desc "Generate new config and save it"
task :configure do
  VerstakConf::export_json
end

desc "Load persisted config"
task :load_config => [] do
  puts "Load config"
  VerstakConf::import_json
end

desc "This command checks the environment for the presence of all components"
task :diagnostic => [] do

  puts '============================================================'
  puts '==================DIAGNOSTIC BUILD SYSTEM==================='
  puts '============================================================'

  error = "###ERROR###: "

  puts "Test drush package"
  if (!system 'drush --version')
    puts error + "drush not found"
    exit
  end
  puts 'drush found'
  puts

  puts "Test mysql cli"
  if (!system 'mysql --version')
    puts error + "mysql not found"
    exit
  end
  puts 'mysql found'
  puts

  puts "Test wget"
  if (!system 'wget --version')
    puts error + "wget not found"
    exit
  end
  puts 'wget found'
  puts

  puts "Test tar"
  if (!system 'tar --version')
    puts error + "tar not found"
    exit
  end
  puts 'tar found'
  puts

  puts "test directory #{VerstakConf::BASE_DIR}"
  if(!File.writable?(VerstakConf::BASE_DIR))
    puts error + "directory is NOT writable"
    exit
  end
  puts "directory is writable"
  puts

  puts '============================================================'
  puts '=================NO ERROR FOUND============================='
  puts '============================================================'
end



desc "Clean build"
task :clean_build => [] do
  system "chmod -R a+w #{VerstakConf::BUILD_BASE_DIR}"

  system "rm -R #{VerstakConf::BUILD_BASE_DIR}"

  system "mysql"+
             " --user=#{VerstakConf::MYSQL_USER}"+
             " --password=#{VerstakConf::MYSQL_PASS}"+
             " -e \"DROP DATABASE IF EXISTS #{VerstakConf::MYSQL_DBNAME}\""

end

task :deploy_build => [:clean_build] do
  Dir::mkdir VerstakConf::BUILD_BASE_DIR
  Dir::mkdir VerstakConf::BUILD_SITE_LOG
  Dir::mkdir VerstakConf::BUILD_SITE_TMP
  Dir::mkdir VerstakConf::BUILD_SITE_DIR_FULL

  rm_f "#{VerstakConf::BASE_DIR}/#{VerstakConf::BUILDS_DIR}/#{VerstakConf::LAST_BUILD_DIR}"
  ln_sf VerstakConf::BUILD_BASE_DIR, "#{VerstakConf::BASE_DIR}/#{VerstakConf::BUILDS_DIR}/#{VerstakConf::LAST_BUILD_DIR}"
end

task :install_drupal => [] do

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS}"+
             " --destination=#{VerstakConf::BUILD_BASE_DIR}"+
             " --drupal-project-rename=#{VerstakConf::SITE_DIR_NAME}"+
             " --cache"+
             " dl #{VerstakConf::DRUSH_DRUPAL_VERSION}"

  system "mysql"+
             " --user=#{VerstakConf::MYSQL_USER}"+
             " --password=#{VerstakConf::MYSQL_PASS}"+
             " -e \"create database #{VerstakConf::MYSQL_DBNAME}\""

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} site-install"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " --db-url=#{VerstakConf::MYSQL_CONNECTION_STRING}"+
             " --account-name=#{VerstakConf::DRUSH_DRUPAL_ACC_NAME}"+
             " --account-pass=#{VerstakConf::DRUSH_DRUPAL_ACC_PASS}"+
             " --account-mail=#{VerstakConf::DRUSH_DRUPAL_ACC_MAIL}"+
             " --site-mail=#{VerstakConf::DRUSH_DRUPAL_SITE_MAIL}"+
             " --site-name=#{VerstakConf::DRUSH_DRUPAL_SITE_NAME}"

  system "chmod -R a+w #{VerstakConf::BUILD_BASE_DIR}"

  system "curl --silent --compressed #{VerstakConf::CRON_URL}"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} user-create"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " test"+
             " --password=test"+
             " --mail=test@diplux.com"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} vset cache 0"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} vset preprocess_css 0"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} vset preprocess_js 0"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"

end

task :drupal_custom_modules_deploy do
  puts "deploy Custom modules"
  copy_recursive("#{VerstakConf::CUSTOMIZATION_PATH}/sites/modules", "#{VerstakConf::BUILD_SITE_DIR_FULL}/sites/all/")
  copy_recursive("#{VerstakConf::CUSTOMIZATION_PATH}/sites/themes", "#{VerstakConf::BUILD_SITE_DIR_FULL}/sites/all/")
  copy_recursive("#{VerstakConf::CUSTOMIZATION_PATH}/sites/libraries", "#{VerstakConf::BUILD_SITE_DIR_FULL}/sites/all/")
end

def copy_recursive(from, to)
  puts "copy from #{from} to #{to}"
  cp_r from, to
end

task :drupal_modules_download do
  file = File.open "#{VerstakConf::CUSTOMIZATION_PATH}/drush/module_list.txt"
  a = file.read.to_s
  mlist = a.strip.gsub(/\n/, ' ')

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} pm-download"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " --cache"+
             " #{mlist}"

  Rake::Task[:drupal_custom_modules_deploy].invoke

end


task :drupal_modules_enable do
  file = File.open "#{VerstakConf::CUSTOMIZATION_PATH}/drush/module_enable_list.txt"
  a = file.read.to_s
  mlist = a.strip.gsub(/\n/, ' ')

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} pm-disable"+ # disable update status for speedup
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " update"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} pm-enable"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " libraries"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} pm-enable"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " #{mlist}"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} vset"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " theme_default"+
             " #{VerstakConf::DRUSH_DRUPAL_SITE_DEFAULT_THEME}"

end

desc "drupal_scripts_run"
task :drupal_scripts_run do

Dir.foreach("#{VerstakConf::CUSTOMIZATION_PATH}/scripts") do |item|
  next if item == '.' or item == '..'

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} php-script"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"+
             " #{VerstakConf::CUSTOMIZATION_PATH}/scripts/#{item}"

  system "chmod -R a+w #{VerstakConf::BUILD_SITE_FILES}"

  system "drush #{VerstakConf::DRUSH_COMMAND_PARAMS} cc all"+
             " --root=#{VerstakConf::BUILD_SITE_DIR_FULL}"
end


end

task :run_vnc_swerver => [:load_config] do
  system "vncserver #{VerstakConf::VNC_DISPLAY}"
end

task :kill_vnc_swerver => [:load_config] do
  system "vncserver -kill #{VerstakConf::VNC_DISPLAY}"
end

desc "Run Functional Testing"
task :functional_testing => [:load_config] do
  Rake::Task[:run_vnc_swerver].invoke
  system "behat"
  Rake::Task[:kill_vnc_swerver].invoke
end

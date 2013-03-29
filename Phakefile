<?php

  require_once __DIR__ . '/lib/phake_utils.php';

  global $VerstakConf;

  $buildNumber = isset($buildNumber) ? $buildNumber : getenv('BUILD_NUMBER') ? : date("Y_M_d-H_i_s");


  task('default', 'new_build');

  desc("Create dev");
  task(
    'dev_create',
    'set_dev_env', 'new_build'
  );


  desc("Update dev");
  task(
    'dev_update',
    'set_dev_env', 'configure', 'drupal_custom_modules_deploy'
  );

  desc("Remove dev");
  task(
    'dev_remove',
//  'set_dev_env', 'configure',
    function () use (&$VerstakConf) {

      //TODO: we should do checks before such operations
      try_command(
        "rm -R $VerstakConf[BUILD_BASE_DIR]",
        "remove build"
      );

      try_command("mysql" .
        " --user=$VerstakConf[MYSQL_USER]" .
        " --password=$VerstakConf[MYSQL_PASS]" .
        " -e \"DROP DATABASE IF EXISTS $VerstakConf[MYSQL_DBNAME]\"");
    }
  );


  desc("Create and deploy snapshot to presentation");
  task(
    'new_build',
    'configure', 'diagnostic', 'deploy_build', 'install_drupal', 'drupal_modules_enable', 'drupal_scripts_run'
  );

  desc("Set development environment");
  task(
    'set_dev_env',
    function () use (&$VerstakConf) {
      putenv('BUILD_NUMBER=dev');
      global $buildNumber;
      $buildNumber = 'dev';
    }
  );


  desc("Generate new config and save it");
  task(
    'configure',
    function () use (&$VerstakConf) {
      file_put_contents('config.json', json_encode($VerstakConf));
    }
  );

  desc("Load persisted config");
  task(
    'load_config',
    function () use (&$VerstakConf) {
      builder_info("Load config");

      $conf = file_get_contents('config.json');
      $VerstakConf = json_decode($conf) + $VerstakConf;
    }
  );

  desc("This command checks the environment for the presence of all components");
  task(
    'diagnostic',
    function () use (&$VerstakConf) {

      builder_info('============================================================');
      builder_info('==================DIAGNOSTIC BUILD SYSTEM===================');
      builder_info('============================================================');

      if (empty($VerstakConf)) {
        builder_error('No config file found');

        writeln("TODO: Write splash scrin text with instruction");
        writeln("Start with README");
        die();
      }

      try_command('drush --version', "Test drush package", 'drush found', "ERROR: drush not found");
      try_command('mysql --version', "Test mysql cli", 'mysql found', "ERROR: mysql not found");
      try_command('wget --version', "Test wget package", 'wget found', "ERROR: wget not found");
      try_command('tar --version', "Test tar package", 'tar found', "ERROR: tar not found");
      try_command('gzip --version', "Test gzip package", 'gzip found', "ERROR: gzip not found");
      try_command('gunzip --version', "Test gunzip package", 'gunzip found', "ERROR: gunzip not found");

      try_command(is_writable($VerstakConf['BASE_DIR']), "Test directory '$VerstakConf[BASE_DIR]'",
        "directory is writable", "directory is NOT writable");

      builder_info('============================================================');
      builder_info('=================NO ERROR FOUND=============================');
      builder_info('============================================================');
    }
  );

  desc("Clean build");
  task(
    'clean_build',
    function () use (&$VerstakConf) {
      try_command("chmod -R a+w $VerstakConf[BUILD_BASE_DIR]", "set permissions on base directory", 'finished',
        "ERROR: chmod -R a+w $VerstakConf[BUILD_BASE_DIR]");

//    try_command("rm -R $VerstakConf[BUILD_BASE_DIR]", "Remove base directory", 'finished',
//      "ERROR: rm -R $VerstakConf[BUILD_BASE_DIR]");

      try_command(
        "mysql" .
          " --user=$VerstakConf[MYSQL_USER]" .
          " --password=$VerstakConf[MYSQL_PASS]" .
          " -e \"DROP DATABASE IF EXISTS $VerstakConf[MYSQL_DBNAME]\""
        ,
        "Remove database");
    }
  );

  desc('Deploy new build');
  task('deploy_build', 'clean_build', function () use (&$VerstakConf) {

      mkdir($VerstakConf['BUILD_BASE_DIR']);
      mkdir($VerstakConf['BUILD_SITE_LOG']);
      mkdir($VerstakConf['BUILD_SITE_TMP']);

      unlink("$VerstakConf[BASE_DIR]/$VerstakConf[BUILDS_DIR]/$VerstakConf[LAST_BUILD_DIR]");
      link($VerstakConf['BUILD_BASE_DIR'], "$VerstakConf[BASE_DIR]/$VerstakConf[BUILDS_DIR]/$VerstakConf[LAST_BUILD_DIR]");

    }
  );

  desc("install Drupal");
  task(
    'install_drupal',
    function () use (&$VerstakConf) {
      builder_message("download files by make-file");

      if (file_exists("$VerstakConf[CUSTOMIZATION_PATH]/custom.make")) {
        builder_info("Custom make-file is exist");
        try_command("drush make $VerstakConf[CUSTOMIZATION_PATH]/custom.make $VerstakConf[BUILD_SITE_DIR_FULL]",
          "Download drupal with custom make file");
      } else {
        builder_message("Custom makefile is not exists. Use default make-file");
        try_command("drush make $VerstakConf[CURRENT_DIR]/default.make $VerstakConf[BUILD_SITE_DIR_FULL]",
          "Download drupal with default make file");
      }

      try_command("mysql" .
          " --user=$VerstakConf[MYSQL_USER]" .
          " --password=$VerstakConf[MYSQL_PASS]" .
          " -e \"create database $VerstakConf[MYSQL_DBNAME]\"",
        "Create database"
      );

      try_command("drush $VerstakConf[DRUSH_COMMAND_PARAMS] site-install" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " --db-url=$VerstakConf[MYSQL_CONNECTION_STRING]" .
          " --account-name=$VerstakConf[DRUSH_DRUPAL_ACC_NAME]" .
          " --account-pass=$VerstakConf[DRUSH_DRUPAL_ACC_PASS]" .
          " --account-mail=$VerstakConf[DRUSH_DRUPAL_ACC_MAIL]" .
          " --site-mail=$VerstakConf[DRUSH_DRUPAL_SITE_MAIL]" .
          " --site-name=$VerstakConf[DRUSH_DRUPAL_SITE_NAME]",
        "Install drupal");

      try_command("chmod -R a+w $VerstakConf[BUILD_BASE_DIR]", "Set install directory writable");

      try_command("drush $VerstakConf[DRUSH_COMMAND_PARAMS] cron", "Run site crons");

      try_command("drush $VerstakConf[DRUSH_COMMAND_PARAMS] user-create" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " test" .
          " --password=test" .
          " --mail=test@diplux.com",
        "Create test user");
    }
  );


  desc('deploy custom modules, themes and libs to sites directory');
  task(
    'drupal_custom_modules_deploy',
    function () use (&$VerstakConf) {
      builder_message("deploy Custom modules");
      try_command("cp -a $VerstakConf[CUSTOMIZATION_PATH]/sites  $VerstakConf[BUILD_SITE_DIR_FULL]/sites/all/",
        'deploy custom modules, themes and libs to sites directory');
    });

  desc('enable modules');
  task(
    'drupal_modules_enable',
    function () use (&$VerstakConf) {

      $file = file("$VerstakConf[CUSTOMIZATION_PATH]/drush/module_enable_list.txt");
      $mlist = implode(' ', $file);

//      disable update status for speedup
      try_command(
        "drush $VerstakConf[DRUSH_COMMAND_PARAMS] pm-disable" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " update",
        "disable update status for speedup");

      try_command(
        "drush $VerstakConf[DRUSH_COMMAND_PARAMS] pm-enable" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " libraries",
        "enable libraries module first");

      try_command(
        "drush $VerstakConf[DRUSH_COMMAND_PARAMS] pm-enable" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " $mlist",
        "enable modules");

      try_command(
        "drush $VerstakConf[DRUSH_COMMAND_PARAMS] vset" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " theme_default" .
          " $VerstakConf[DRUSH_DRUPAL_SITE_DEFAULT_THEME]",
        "enable default theme");
    });

  desc("drupal_scripts_run");
  task(
    'drupal_scripts_run',
    function () use ($VerstakConf) {

      $files = sort(glob("$VerstakConf[CUSTOMIZATION_PATH]/scripts/*"));

      foreach ($files as $file) {


        try_command("drush $VerstakConf[DRUSH_COMMAND_PARAMS] php-script" .
          " --root=$VerstakConf[BUILD_SITE_DIR_FULL]" .
          " $VerstakConf[CUSTOMIZATION_PATH]/scripts/$file",
        "Run script $VerstakConf[CUSTOMIZATION_PATH]/scripts/$file");
      }


      //TODO: move to separate task
      try_command("chmod -R a+w $VerstakConf[BUILD_SITE_FILES]",
      "Change permissions on build directory");
    });



/*

desc "Run Functional Testing"
task :functional_testing => [:load_config] do
  Rake::Task[:run_vnc_swerver].invoke
  system "behat"
  Rake::Task[:kill_vnc_swerver].invoke
end

*/

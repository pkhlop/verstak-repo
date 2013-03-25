<?php

  global $VerstakConf;

  $VerstakConf = isset($VerstakConf) ? $VerstakConf : array();

//  DIRS
  $VerstakConf += array('CURRENT_DIR' => __DIR__);

  $VerstakConf += array('BUILD_NUMBER' => $buildNumber);
  $VerstakConf += array('BUILD_VERSION' => "verstak_7_01");
  $VerstakConf += array('BASE_DIR' => "/var/www/verstak");
  $VerstakConf += array('BUILDS_DIR' => "builds");
  $VerstakConf += array('LAST_BUILD_DIR' => "lastbuild");
  $VerstakConf += array('BUILD_BASE_DIR' => "$VerstakConf[BASE_DIR]/$VerstakConf[BUILDS_DIR]/$VerstakConf[BUILD_NUMBER]");
  $VerstakConf += array('SITE_DIR_NAME' => "www");
  $VerstakConf += array('BUILD_SITE_DIR_FULL' => "$VerstakConf[BUILD_BASE_DIR]/$VerstakConf[SITE_DIR_NAME]");
  $VerstakConf += array('BUILD_SITE_LOG' => $VerstakConf['BUILD_BASE_DIR'] + "/logs");
  $VerstakConf += array('BUILD_SITE_TMP' => $VerstakConf['BUILD_BASE_DIR'] + "/tmp");
  $VerstakConf += array('BUILD_SITE_FILES' => $VerstakConf['BUILD_SITE_DIR_FULL'] + "/sites/default/files");
  $VerstakConf += array('BUILD_BASE_URL' => "http://localhost/verstak-ci/$VerstakConf[BUILDS_DIR]");
  $VerstakConf += array('BUILD_URL' => "$VerstakConf[BUILD_BASE_URL]/$VerstakConf[BUILD_NUMBER]/$VerstakConf[SITE_DIR_NAME]");
  $VerstakConf += array('CRON_URL' => "$VerstakConf[BUILD_URL]/$VerstakConf[SITE_DIR_NAME]/cron.php");
  $VerstakConf += array('DISTR_DIR' => $VerstakConf['BASE_DIR'] + "/distr");
  $VerstakConf += array('VERSTAK_DIR' => "$VerstakConf[CURRENT_DIR]");
  $VerstakConf += array('IMPORTER_DIR' => "$VerstakConf[VERSTAK_DIR]/importer");
  $VerstakConf += array('DRUSH_DIR' => "$VerstakConf[CURRENT_DIR]/sites/drush");


//  DRUSH
  $VerstakConf += array('DRUSH_COMMAND_PARAMS' => "-y");
  $VerstakConf += array('DRUSH_DRUPAL_VERSION' => "drupal-7");
  $VerstakConf += array('DRUSH_DRUPAL_ACC_NAME' => "admin");
  $VerstakConf += array('DRUSH_DRUPAL_ACC_PASS' => "<PASS>");
  $VerstakConf += array('DRUSH_DRUPAL_ACC_MAIL' => "mail@example.com");
  $VerstakConf += array('DRUSH_DRUPAL_SITE_MAIL' => "mail@example.com");
  $VerstakConf += array('DRUSH_DRUPAL_SITE_NAME' => "$VerstakConf[BUILD_VERSION].$VerstakConf[BUILD_NUMBER]");
  $VerstakConf += array('DRUSH_DRUPAL_SITE_DEFAULT_THEME' => "batik");

//  MySQL
  $VerstakConf += array('MYSQL_USER' => "verstak");
  $VerstakConf += array('MYSQL_PASS' => "<PASS>");
  $VerstakConf += array('MYSQL_HOST' => "localhost");
  $VerstakConf += array('MYSQL_DBNAME' => str_replace('-', '_', "$VerstakConf[MYSQL_USER]_$VerstakConf[BUILD_VERSION]_$VerstakConf[BUILD_NUMBER]"));
  $VerstakConf += array('MYSQL_CONNECTION_STRING' => "mysql://$VerstakConf[MYSQL_USER]:$VerstakConf[MYSQL_PASS]@$VerstakConf[MYSQL_HOST]/$VerstakConf[MYSQL_DBNAME]");

//  Content Settings
  $VerstakConf += array('PROHIBITED_FIELDS_LIST' => 'field_src_gift,field_reserved,field_reservation_date,field_purchased,field_anonymously,field_user_reserved_by,field_received,field_received_when,field_received_from');

//  def self.export_json(file='config.json'));
//    # save config in JSON for php scripts);
//    conf = Hash.new);
//    VerstakConf.constants.each do |name|);
//      conf[name] = VerstakConf.const_get(name));
//    end);
//
//    file = File.new(file, 'w'));
//    file.write(conf.to_json));
//    file.close);
//  end);
//
//  def self.import_json(file='config.json'));
//    file = File.new(file, 'r'));
//    conf = JSON.parse(file.read()));
//    file.close);
//    );
//    conf.each do |key, val|);
//      VerstakConf::redef_without_warning(key, val));
//      puts "#{key} = #{val}");
//    end);
//    );
//  end);




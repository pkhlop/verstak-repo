<?php

if(!defined("DRUPAL_BOOTSTRAP_CONFIGURATION")){
    chdir(ImportConfig::getConfig()->engine_path);
    $_SERVER['REMOTE_ADDR'] = '127.0.0.1';
    $_SERVER['REQUEST_METHOD'] = 'GET';
    require_once 'includes/bootstrap.inc';
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
}


//global $db_url; // the internal variable that contains database link
//$default_db = $db_url;
//$db_url = array('default' => $default_db);
//$db_url['importdb'] = ImportConfig::connection;

require_once ImportConfig::getConfig()->importer_path.'/classes/Storage.inc';
foreach (glob(ImportConfig::getConfig()->importer_path.'/classes/*.inc') as $file){
    require_once $file;
}
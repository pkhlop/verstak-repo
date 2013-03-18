$buildnumber = 'dev'

class VerstakConf
  VERSTAK_DIR = '<full path to verstak project, for example /home/user/projects/verstak-repo>'
  CUSTOMIZATION_PATH = File.expand_path(File.dirname(__FILE__))

  BASE_DIR = "/var/www/projects/"
  DRUSH_DRUPAL_ACC_PASS = "password"
  MYSQL_USER = "user"
  MYSQL_PASS = "password"
  DRUSH_DRUPAL_SITE_DEFAULT_THEME = "custom-theme-name"
end


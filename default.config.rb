require "rubygems"
require 'json'

class Object
  def def_if_not_defined(const, value)
    mod = self.is_a?(Module) ? self : self.class
    mod.const_set(const, value) unless mod.const_defined?(const)
  end

  def redef_without_warning(const, value)
    mod = self.is_a?(Module) ? self : self.class
    mod.send(:remove_const, const) if mod.const_defined?(const)
    mod.const_set(const, value)
  end
end


class VerstakConf

  #DIRS#
  def_if_not_defined :CURRENT_DIR, File.expand_path(File.dirname(__FILE__))
  def_if_not_defined :BUILD_NUMBER, $buildnumber
  def_if_not_defined :BUILD_VERSION, "verstak_7_01"
  def_if_not_defined :BASE_DIR, "/var/www/verstak"
  def_if_not_defined :BUILDS_DIR, "builds"
  def_if_not_defined :LAST_BUILD_DIR, "lastbuild"
  def_if_not_defined :BUILD_BASE_DIR, "#{BASE_DIR}/#{BUILDS_DIR}/#{BUILD_NUMBER}"
  def_if_not_defined :SITE_DIR_NAME, "www"
  def_if_not_defined :BUILD_SITE_DIR_FULL, "#{BUILD_BASE_DIR}/#{SITE_DIR_NAME}"
  def_if_not_defined :BUILD_SITE_LOG, BUILD_BASE_DIR + "/logs"
  def_if_not_defined :BUILD_SITE_TMP, BUILD_BASE_DIR + "/tmp"
  def_if_not_defined :BUILD_SITE_FILES, BUILD_SITE_DIR_FULL + "/sites/default/files"

  def_if_not_defined :BUILD_BASE_URL, "http://localhost/verstak-ci/#{BUILDS_DIR}"
  def_if_not_defined :BUILD_URL, "#{BUILD_BASE_URL}/#{BUILD_NUMBER}/#{SITE_DIR_NAME}"
  def_if_not_defined :CRON_URL, "#{BUILD_URL}/#{SITE_DIR_NAME}/cron.php"

  def_if_not_defined :DISTR_DIR, BASE_DIR + "/distr"

  def_if_not_defined :VERSTAK_DIR, "#{CURRENT_DIR}"
  def_if_not_defined :IMPORTER_DIR, "#{VERSTAK_DIR}/importer"
  def_if_not_defined :DRUSH_DIR, "#{CURRENT_DIR}/sites/drush"


  #DRUSH#
  def_if_not_defined :DRUSH_COMMAND_PARAMS, "-y"
  def_if_not_defined :DRUSH_DRUPAL_VERSION, "drupal-7"
  def_if_not_defined :DRUSH_DRUPAL_ACC_NAME, "admin"
  def_if_not_defined :DRUSH_DRUPAL_ACC_PASS, "<PASS>"
  def_if_not_defined :DRUSH_DRUPAL_ACC_MAIL, "mail@example.com"
  def_if_not_defined :DRUSH_DRUPAL_SITE_MAIL, "mail@example.com"
  def_if_not_defined :DRUSH_DRUPAL_SITE_NAME, "#{BUILD_VERSION}.#{BUILD_NUMBER}"
  def_if_not_defined :DRUSH_DRUPAL_SITE_DEFAULT_THEME, "batik"

  #MySQL#
  def_if_not_defined :MYSQL_USER, "verstak"
  def_if_not_defined :MYSQL_PASS, "<PASS>"
  def_if_not_defined :MYSQL_HOST, "localhost"
  def_if_not_defined :MYSQL_DBNAME, "#{MYSQL_USER}_#{BUILD_VERSION}_#{BUILD_NUMBER}".gsub('-', '_')
  def_if_not_defined :MYSQL_CONNECTION_STRING, "mysql://#{VerstakConf::MYSQL_USER}:#{VerstakConf::MYSQL_PASS}@#{VerstakConf::MYSQL_HOST}/#{VerstakConf::MYSQL_DBNAME}"

  #Content Settings#
  def_if_not_defined :PROHIBITED_FIELDS_LIST, 'field_src_gift,field_reserved,field_reservation_date,field_purchased,field_anonymously,field_user_reserved_by,field_received,field_received_when,field_received_from'

  def self.export_json(file='config.json')
    # save config in JSON for php scripts
    conf = Hash.new
    VerstakConf.constants.each do |name|
      conf[name] = VerstakConf.const_get(name)
    end

    file = File.new(file, 'w')
    file.write(conf.to_json)
    file.close
  end
  
  def self.import_json(file='config.json')
    file = File.new(file, 'r')
    conf = JSON.parse(file.read())
    file.close
    
    conf.each do |key, val|
      VerstakConf::redef_without_warning(key, val)
    end
    
  end
end

<?php
define("IMPORT_ENV_WEB", 'web');
define("IMPORT_ENV_SHELL", 'shell');
define("IMPORT_ENV", isset($_SERVER["REQUEST_METHOD"]) ? IMPORT_ENV_WEB : IMPORT_ENV_SHELL);

global $json_conf;

$json_conf = file_get_contents(__DIR__.'/../../../config.json');

$json_conf = json_decode($json_conf, true);

class ImportConfig{

    public $base_path;
    public $engine_path;
    public $importer_path;
    public $files_tmp_dir;

    public $category_name;
    public $categories;
    public $manufactures;
    public $features;
    public $features_name;
    public $product_type;
    public $image_c_path;
    public $manuf_name;
    public $image_f_path;

    public $env;

    public $connection;

    private static $config = false;
    /**
     *
     * @return ImportConfig 
     */
    static function getConfig(){
        global $json_conf;
        
        if(ImportConfig::$config) return ImportConfig::$config;
        
        $config = new ImportConfig();

        $config->base_path =     $json_conf['BASE_DIR'];
        $config->engine_path =   $json_conf['BUILD_SITE_DIR_FULL'];
        $config->importer_path =   __DIR__.'/..';
        $config->files_tmp_dir = $json_conf['BUILD_SITE_TMP'];
        $config->files_base_path = $json_conf['BASE_DIR_FILES'];
        
        $config->categories = $json_conf['CATEG'];
        $config->category_name = $json_conf['CATEG_NAME'];
        $config->manufactures = $json_conf['MANUFAC'];
        $config->manuf_name = $json_conf['MANUFAC_NAME'];
        $config->features = $json_conf['FEATURES'];
        $config->features_name = $json_conf['FEATURES_NAME'];
        $config->product_type = $json_conf['PRODUCT_TYPE'];
        $config->image_c_path = $json_conf['IMG_C_PATH'];
        $config->image_f_path = $json_conf['IMG_F_PATH'];
        $config->image_m_path = $json_conf['IMG_M_PATH'];

        $config->connection = $json_conf['CONNECTION'];

        $config->env = IMPORT_ENV;
        
        ImportConfig::$config = $config;
        return ImportConfig::$config;
    }
}
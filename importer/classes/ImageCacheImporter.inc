<?php
class ImageCacheImporter{
    private $storage;

    public function __construct(ImageCacheStorage $storage) {
        $this->storage = $storage;
    }

    public function Import(){
        $this->storage->Load();
        $presets_files = $this->storage->Get();

        include_once(drupal_get_path('module', 'imagecache_actions') .'/imagecache_actions.module');
        include_once(drupal_get_path('module', 'imagecache_actions') .'/image_styles_admin/image_styles_admin.module');
        include_once(drupal_get_path('module', 'imagecache_actions') .'/image_styles_admin/image_styles_admin.inc');

        foreach ($presets_files as $preset_file){
          $preset = '';
          include $preset_file;

          if (!is_array($preset)) {
            $preset = array($preset);
          }

          foreach($preset as $line) {
            $this->saveFromJSON($line);
          }
        }
    }

    public function saveFromJSON($json) {

      try{

        $style = image_styles_admin_import_extract_style($json);
        $new_style = image_style_save($style);
        if (isset($new_style['is_new'])) {
          drush_log(t('Style !name has been created.', array('!name' => $style['name'])), 'ok');
        }
        else {
          drush_log(t('Style !name has been updated.', array('!name' => $style['name'])), 'ok');
        }
      } catch (Exception $e) {
        drush_log("Error import image style: \n$json\n", 'error');
      }

    }
}
<?php
class ImageCacheImporter{
    private $storage;

    public function __construct(ImageCacheStorage $storage) {
        $this->storage = $storage;
    }

    public function Import(){
        $this->storage->Load();
        $presets_files = $this->storage->Get();
	
        foreach ($presets_files as $preset_file){
          include $preset_file;
          $effect = $preset['effects'];
          $style = image_style_save(array('name' => $preset['presetname']));
          $effect['isid'] = $style['isid'];
          image_effect_save($effect);
        }
    }
}
<?php

class ImageCacheStorage extends Storage{
    private $presets = array();

    public function Load(){
        $this->presets = glob($this->path);
    }

    public function Get() {
        return $this->presets;
    }

}
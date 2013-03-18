<?php

class BlockStorage extends Storage{
    private $blocks = array();
    
    public function Load(){
        $blocks_files = glob($this->path);
        $blocks = array();
        foreach ($blocks_files as $file){
            $block = false;
            include $file;
            if ($block !== false) $blocks[] = $block;
        }
        $this->blocks = $blocks;
    }
    
    public function Get() {
        return $this->blocks;
    }
    
}
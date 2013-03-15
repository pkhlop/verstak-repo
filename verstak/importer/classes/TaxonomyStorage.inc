<?php

class TaxonomyStorage extends Storage{
    private $vocabs = array();
    
    public function Load(){
        $taxonomy_files = glob($this->path);
        $vocabs = array();
        foreach ($taxonomy_files as $file){
            $vocab = false;
            include $file;
            if ($vocab !== false) $vocabs[] = $vocab;
        }
        $this->vocabs = $vocabs;
    }
    
    public function Get() {
        return $this->vocabs;
    }
    
}
<?php

class NodeStorage extends Storage{
    private $nodes = array();
    
    public function Load(){
        $node_files = glob($this->path);
        $nodes = array();
        foreach ($node_files as $file){
            $node = false;
            include $file;
            if ($node !== false) $nodes[] = $node;
        }
        $this->nodes = $nodes;
    }
    
    public function Get() {
        return $this->nodes;
    }
    
}
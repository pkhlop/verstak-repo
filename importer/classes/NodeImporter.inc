<?php
class NodeImporter{
    private $storage;
    
    public function __construct(NodeStorage $storage) {
        $this->storage = $storage;
    }
    
    public function Import(){
        $this->storage->Load();
        $nodes = $this->storage->Get();
        
        
        foreach ($nodes as $node){
            node_save($node);
            path_set_alias('node/'.$node->nid, $node->path);
        }
               
    }
    
}
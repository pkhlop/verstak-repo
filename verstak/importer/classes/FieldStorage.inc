<?php

class FieldStorage extends Storage{
    private $fields = array();
    
    public function Load(){
        $fields_files = glob($this->path);
        $fields = array();
        foreach ($fields_files as $file){
            include $file;
        }
        $this->fields = $fields;
    }
    
    public function Get() {
        return $this->fields;
    }
    
}
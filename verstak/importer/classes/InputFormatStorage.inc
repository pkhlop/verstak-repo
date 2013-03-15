<?php

class InputFormatStorage extends Storage{
    private $inputs = array();
    
    public function Load(){
        $inputs_files = glob($this->path);
        $inputs = array();
        foreach ($inputs_files as $file){
            $input = false;
            include $file;
            if ($input !== false) $inputs[] = $input;
        }
        $this->inputs = $inputs;
    }
    
    public function Get() {
        return $this->inputs;
    }
    
}
<?php

class ProfileFieldsStorage extends Storage{
    private $profile_fields = array();
    
    public function Load(){
        $profile_field_files = glob($this->path);
        $profile_fields = array();
        foreach ($profile_field_files as $file){
            $profile_field = false;
            include $file;
            if ($profile_field !== false) $profile_fields[] = $profile_field;
        }
        $this->profile_fields = $profile_fields;
    }
    
    public function Get() {
        return $this->profile_fields;
    }
    
}
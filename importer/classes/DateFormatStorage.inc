<?php

class DateFormatStorage extends Storage{
    private $date_formats = array();
    
    public function Load(){
        $date_format_files = glob($this->path);
        $date_formats = array();
        foreach ($date_format_files as $file){
            $date_format = false;
            include $file;
            if ($date_format !== false) $date_formats[] = $date_format;
        }
        $this->date_formats = $date_formats;
    }
    
    public function Get() {
        return $this->date_formats;
    }
    
}
<?php

class ViewsStorage extends Storage{
    private $views = array();
    
    public function Load(){
        $views_files = glob($this->path);

        $views = array();
        foreach ($views_files as $file){
            $view = false;
            include $file;
            if ($view !== false) $views[] = $view;
        }
        $this->views = $views;

    }
    
    public function Get() {
        return $this->views;
    }
    
}



<?php

class MenuStorage extends Storage{
    private $menus = array();
    
    public function Load(){
        $menu_files = glob($this->path);
        $menus = array();
        foreach ($menu_files as $file){
            $menu = false;
            include $file;
            if($menu !== false) $menus[] = $menu;
        }
        $this->menus = $menus;
    }
    
    public function Get() {
        return $this->menus;
    }
    
}
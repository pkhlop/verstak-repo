<?php

class ContentTypeStorage extends Storage{
  private $types = array();

  public function Load(){
    $type_files = glob($this->path);
    $types = array();
    foreach ($type_files as $file){
      $type = false;
      include $file;
      if ($type !== false) $types[] = $type;
    }
    $this->types = $types;
  }

  public function Get() {
    return $this->types;
  }
}
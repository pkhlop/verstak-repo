<?php

class ContextStorage extends Storage
{
  private $contexts = array();

  public function Load()
  {
    $context_files = glob($this->path);

    $contexts = array();
    foreach ($context_files as $file) {
      $context = false;
      include $file;
      if ($context !== false) $contexts[] = $context;
    }
    $this->contexts = $contexts;

  }

  public function Get()
  {
    return $this->contexts;
  }

}

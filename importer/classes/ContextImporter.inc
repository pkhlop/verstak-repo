<?php
class ContextImporter{
    private $storage;
    
    public function __construct(ContextStorage $storage) {
        $this->storage = $storage;
    }
    
    public function Import(){
        $this->storage->Load();
        $contexts = $this->storage->Get();

        foreach ($contexts as $context){
          echo "\nImport {$context[name]}\n";
          $result = $this->context_import($context['name'], $context['macro']);
          echo "\nresult ".var_export($result)."\n";
        }
    }
    
    private function context_import($context_name, $context_macro) {

      eval($context_macro);

      context_save($context);

      return true;
    }
}
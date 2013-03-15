<?php
class InputFormatImporter{
    private $storage;

    public function __construct(InputFormatStorage $storage) {
        $this->storage = $storage;
    }

    public function Import(){
        $this->storage->Load();

        $inputs = $this->storage->Get();
        
        foreach ($inputs as $input){
            echo "Input format {$input[name]}\n";
            $this->SaveInput($input);
        }
    }

    protected function SaveInput($input) {
        $form = $form_state = array();
        $form_state['values'] = $input;
        filter_admin_format_form_submit($form, $form_state);
    }

    public static function getFidByName($name){
        
        if(is_numeric($name)) return intval($name);
        
        $formats = filter_formats();
        
        foreach ($formats as $id => $format) {
            if($format->name == $name) return $format->format;
        }
        
        return variable_get('filter_default_format', 1);
    }

}

<?php
function import_terms($cats, $vid, $ipath){

    $tcount = count($cats);
    $tcurrent = 1;
    foreach ($cats as $key => $cat){
        if(isset($cat['parentid']) && isset($cats[$cat['parentid']])){
            $parent = $cats[$cat['parentid']];
            $cat['parent'] = array($parent['tid']);
        }elseif(isset($cat['parentid']) && $cat['parentid']==0){
            echo "ROOT TERM----------------->\n";
        }else{
            echo '[ERROR]: parent not found===============================>\n';
        }

        $cat['vid'] = $vid;
        $result = taxonomy_save_term($cat);
        $cats[$key] = $cat;

        //if category image exists
        if($cat['image_path']){
            //get image name from stored image path
            $cat['image_name'] = end(explode('/', $cat['image_path']));
            //build full path image stored in
            $cat['src_image_path'] = ImportConfig::getConfig()->files_base_path.$ipath.$cat['image_name'];
            //build full path for image temp storage. transliterate and cleanup image name
            $cat['tmp_image_path'] = ImportConfig::getConfig()->files_tmp_dir.transliteration_clean_filename($cat['image_name']);

            //copy image to temp storage to convert name and leave source image untouchable
            echo "copy({$cat['src_image_path']},  {$cat['tmp_image_path']});\n";
            copy($cat['src_image_path'],  $cat['tmp_image_path']);

            //build additional taxonomy save form fields
            $form_values = array();
            $form_values['tid'] = $cat['tid'];
            $form_values['taxonomy_image_current_image_delete'] = false;
            $form_values['taxonomy_image_external'] = $cat['tmp_image_path'];

            //run hook_taxonomy in taxonomy_image module
            echo "import image:".$form_values['taxonomy_image_external']."\n";
            taxonomy_image_taxonomy('update', 'term', $form_values);

            //remove temprorary files
            unlink($cat['tmp_image_path']);
        }

        echo sprintf("Name='%s';\n id='%s'; \t parentid='%s'; \t parent tid='%s'; \t parent tid='%s';\n (%d from %d)\n ",
                $cat['name'],$cat['categoryid'],$cat['parentid'],$cat['parent'][0],$cat['tid'], $tcurrent, $tcount);
        $tcurrent++;
    }

    return $cats;

}

function get_vid_by_name($name){
    $vocabularies = taxonomy_get_vocabularies();
    foreach ($vocabularies as $vocab){
        if($vocab->name == $name){
            return $vocab->vid;
        }
    }

    return false;
}
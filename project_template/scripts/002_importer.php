<?php

require_once __DIR__ . '/../include/import_config.inc';
require_once __DIR__ . '/../include/init.inc';

global $user;
$user = user_load(1);

echo "Start Context Import ==========================\n";
$storage = new ContextStorage(ImportConfig::getConfig()->importer_path.'/data/contexts/*.inc');
$context = new ContextImporter($storage);
$context->Import();
die();

echo "Start Date Format Import ==========================\n";
$storage = new DateFormatStorage(ImportConfig::getConfig()->importer_path.'/data/date_format/*.inc');
$importer = new DateFormatImporter($storage);
$importer->Import();

echo "Start Content Type Import ==========================\n";
$storage = new ContentTypeStorage(ImportConfig::getConfig()->importer_path.'/data/content_type/*.inc');
$importer = new ContentTypeImporter($storage);
$importer->Import();

//echo "Start Input Format Import ==========================\n";
//$storage = new InputFormatStorage(ImportConfig::getConfig()->importer_path.'/data/input_formats/*.inc');
//$importer = new InputFormatImporter($storage);
//$importer->Import();

echo "Start Taxonomy Import ==========================\n";
$storage = new TaxonomyStorage(ImportConfig::getConfig()->importer_path.'/data/taxonomy/*.inc');
$importer = new TaxonomyImporter($storage);
$importer->Import();

echo "Start ImageCache Presets Outline ==========================\n";
$storage = new ImageCacheStorage(ImportConfig::getConfig()->importer_path.'/data/presets/*.inc');
$importer = new ImageCacheImporter($storage);
$importer->Import();

echo "Start Views Import ==========================\n";
$storage = new ViewsStorage(ImportConfig::getConfig()->importer_path.'/data/views/*.inc');
$importer = new ViewsImporter($storage);
$importer->Import();

//echo "Start Node Import ==========================\n";
//$storage = new NodeStorage(ImportConfig::getConfig()->importer_path.'/data/nodes/*.inc');
//$importer = new NodeImporter($storage);
//$importer->Import();

echo "Start Menu Import ==========================\n";
$storage = new MenuStorage(ImportConfig::getConfig()->importer_path.'/data/menus/*.inc');
$importer = new MenuImporter($storage);
$importer->Import();

echo "Start Block Outline ==========================\n";
$storage = new BlockStorage(ImportConfig::getConfig()->importer_path.'/data/blocks/*.inc');
$importer = new BlockImporter($storage);
$importer->Import();

echo "Start Context Import ==========================\n";
$storage = new ContextStorage(ImportConfig::getConfig()->importer_path.'/data/contexts/*.inc');
$context = new ContextImporter($storage);
$context->Import();

//echo "Start Profile Fields Creation ==========================\n";
//$storage = new ProfileFieldsStorage(ImportConfig::getConfig()->importer_path.'/data/profile/*.inc');
//$importer = new ProfileFieldsImporter($storage);
//$importer->Import();



variable_set("cache", 1);
variable_set("page_compression", 1);
variable_set("block_cache", 1);

variable_set("preprocess_css", 0);
variable_set("preprocess_js", 0);

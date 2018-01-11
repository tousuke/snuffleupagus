--TEST--
Samesite on session cookies
--SKIPIF--
<?php if (!extension_loaded("snuffleupagus")) die "skip"; ?>
--INI--
sp.configuration_file={PWD}/config/session_start_cookies.ini
--FILE--
<?php
session_start();
var_dump(headers_list());
?>
--EXPECT--
array(0) {
}

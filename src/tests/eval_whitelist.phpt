--TEST--
Eval whitelist
--SKIPIF--
<?php if (!extension_loaded("snuffleupagus")) die "skip"; ?>
--INI--
sp.configuration_file={PWD}/config/eval_whitelist.ini
--FILE--
<?php 
function my_fun($p) {
	return "my_fun: $p";
}

function my_other_fun($p) {
	return "my_other_fun: $p";
}

$a = my_fun("1337 1337 1337");
echo "Outside of eval: $a\n";
eval('$a = my_fun("1234");');
echo "After allowed eval: $a\n";
eval('$a = my_other_fun("1234");');
echo "After eval: $a\n";
?>
--EXPECTF--
Outside of eval: my_fun: 1337 1337 1337
After allowed eval: my_fun: 1234
[snuffleupagus][0.0.0.0][Eval_whitelist][drop] The function 'my_other_fun' isn't in the eval whitelist, dropping its call.

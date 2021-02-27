# nodert modules

Recently nodert started to fail to build because of the lack of the link option called `/bigobj`

for example `windows.storage`

Please refer to the issue on their Github

https://github.com/NodeRT/NodeRT/issues/143


## solution

```
$ npm install @nodert-win10-rs4/windows.storage --ignore-scripts
```

and move the package from the node_modules to this nodert directory


```
$ mv node_modules/@nodert-win10-rs4/windows.storage .
```

and then add `/bigobj` into binding.gyp

```
"msvs_settings": {
    "VCCLCompilerTool": {
    -        "AdditionalOptions": ["/ZW"],
    +        "AdditionalOptions": ["/ZW", "/bigobj"],
	     "DisableSpecificWarnings": [4609]
    }
 }
```

Now you can add @nodert-win10-rs4/windows.storage using `file:`

```
    "@nodert-win10-rs4/windows.storage": "file:../packages/nodert/windows.storage",
```

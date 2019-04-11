{
  "targets": [
    {
      "target_name": "node-windpapi",
      "sources": [ "src/node-windpapi.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "include"
      ]
    }
  ]
}
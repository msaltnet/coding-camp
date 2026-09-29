# Local Codelab assets

These unmodified runtime files are vendored so lessons do not depend on the
unavailable `storage.googleapis.com/claat-public` bucket.

## Source

All five files come from Google's Codelabs tools repository at commit
`873fe39d02dcbd43005a5c44f6310595d6d9aa3e`:

https://github.com/googlecodelabs/tools/tree/873fe39d02dcbd43005a5c44f6310595d6d9aa3e/site/app/elements/codelab-elements

Download URL pattern:
`https://raw.githubusercontent.com/googlecodelabs/tools/873fe39d02dcbd43005a5c44f6310595d6d9aa3e/site/app/elements/codelab-elements/FILE`

Retrieved on 2026-09-29. This is a preserved official repository bundle;
it is not claimed to be byte-identical to the unavailable bucket.

## Licenses

- Codelab CSS/JS and Google Code Prettify: Apache-2.0, see `LICENSE`.
- Custom Elements polyfill and native shim: Polymer BSD license, see
  `LICENSE.custom-elements` and the copyright notice in `native-shim.js`.
  License source: https://github.com/webcomponents/custom-elements/blob/v1.0.8/LICENSE.md

## Regenerating lessons

Run `build.bat` from Windows. After successful CLaaT exports it runs
`scripts/localize-assets.ps1`, replacing the five external URLs with
`../assets/codelab/FILE`. Relative URLs work on the custom domain and under
a GitHub Pages repository prefix.

After running CLaaT manually, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/localize-assets.ps1
```

The Google Fonts and support/analytics integrations remain separate external
services. These five local files cover the lesson layout and navigation.

## SHA-256

| File | SHA-256 |
| --- | --- |
| codelab-elements.css | 8de5365ad7dc3152a912cdc2ea718690d5f9693bb680c0e14a94b8e7e12ef6b6 |
| codelab-elements.js | 07a413ba8483bf70f8f289bbb8e16f73ad27b93f74e5acd17e82597a6a5d16f8 |
| custom-elements.min.js | e70470624aa234bd89e888a0a124a37dc07011c39ccf902ae8fb8c3e232d50b3 |
| native-shim.js | 1eb661a55aea2395c118280a06bcb0c849d83f8fd29839bd27b46afdce2ee3c6 |
| prettify.js | 180614baf42339bf7909fd8fbdd8ad1c984285c495f21e72a9ad99d425ed9b60 |


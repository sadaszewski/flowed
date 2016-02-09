Flow/Vector Field Editor
========================

Good news for all fans of my minimalist
<a href="http://algoholic.eu/flow-field-editor-still-alive/">Flow Editor</a>.
The software is now open source (under 2-clause BSD license) and available on
GitHub under the name <a href="https://github.com/sadaszewski/flowed" target="_blank">flowed</a>.
To build it you will need as well: <a href="https://github.com/sakov/nn-c" target="_blank">nn-c</a>
and <a href="https://cran.r-project.org/web/packages/akima/index.html" target="_blank">akima</a>.
They’re used just for interpolation (natural neighbor and bicubic respectively) and can be linked
statically. Fortran compiler is required to compile akima. There’s also a Mac OS X version available
in the releases section on GitHub:
<a href="https://github.com/sadaszewski/flowed/releases" target="_blank">here</a>.
Hope you enjoy and maybe develop it further.

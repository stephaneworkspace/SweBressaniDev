//
// Created by Stéphane on 22.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

const char* SIGNS_BELIER_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMzE2LjIgMjg3LjUiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDMxNi4yIDI4Ny41OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6I0ZGMDAwMDt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxOTciIGNsYXNzPSJzdDAiIGQ9Ik02Mi4xLDBDMzguNywwLDE3LjIsMTUuNyw3LjUsMzYuN0MtNS4zLDY0LjEtMC45LDk3LjUsMTQuNCwxMjNjNC4yLDUuNSwxMi41LDYsMTcuNiwxLjYKCQkJYzYuNy0zLjcsMTUuMy03LjcsMTcuNC0xNS44YzEuMS05LTYuMy0xNS45LTcuNC0yNC41QzM4LjIsNzAsNDAuOCw1MS45LDU0LDQzLjFjMTAuNy01LjksMjMuNiwwLjQsMzEuNCw4LjQKCQkJYzIxLjMsMTkuOSwzMC4xLDQ5LjEsMzcsNzYuNWMxMi41LDUyLjIsMTQuNSwxMDYuMSwxNi4yLDE1OS41aDM4LjdjMi40LTQ3LjYsMS45LTk1LjUsMTIuNC0xNDIuMmM2LjYtMzEuNiwxNi4zLTYzLjcsMzYuOS04OS4yCgkJCWM3LjctOC45LDE5LjItMTcuOCwzMS41LTE0LjljMTMuNSw0LjcsMTguMywyMSwxNy4yLDM0Yy0wLjYsMTEtNS44LDIwLjktOS4yLDMxLjJjLTAuOCw3LjQsNi4xLDEyLjUsMTIuMywxNC44CgkJCWM1LjcsMy42LDEzLjMsOSwyMCw0LjZjNy4zLTUsOC41LTE0LjUsMTIuMi0yMmMxMC41LTI4LjQsNi45LTYzLjctMTUtODUuOEMyNzguNywwLjUsMjUwLjktNC45LDIyOC43LDUKCQkJYy0yMiw5LTM3LjcsMjguMy00OC45LDQ4LjZjLTksMTYtMTYuNCwzMy0yMS44LDUwLjVjLTEwLjEtMzMuNS0yNS43LTY3LjUtNTMuOC04OS43QzkyLjEsNS40LDc3LjItMC4xLDYyLjEsMEw2Mi4xLDB6Ii8+Cgk8L2c+CjwvZz4KPC9zdmc+";
const char* SIGNS_TAUREAU_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjY4LjQgMjg5IiBzdHlsZT0iZW5hYmxlLWJhY2tncm91bmQ6bmV3IDAgMCAyNjguNCAyODk7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDojOTk2NjMzO30KPC9zdHlsZT4KPGcgaWQ9ImxheWVyMSI+Cgk8ZyBpZD0iZzQzMjIiPgoJCTxwYXRoIGlkPSJwYXRoNDE3NSIgY2xhc3M9InN0MCIgZD0iTTQuNCwwQy0zLDEuOCwxLjYsMTEuMiwwLjMsMTYuNGMwLDcuNywwLDE1LjQsMCwyMy4yYzkuNi0wLjgsMjEuMS0xLjIsMjcuNyw3LjIKCQkJYzIwLjcsMTkuNiwzMi42LDQ2LjYsNTMuMSw2Ni40Yy0zMSwxOS40LTQ3LjMsNTguNS00MSw5NC4zYzUuMywzNC43LDMwLjQsNjYuNSw2NC41LDc2LjdjMzMsMTAuOSw3Mi40LDMsOTYuNS0yMi43CgkJCWMzMC4yLTMwLjYsMzguNC04Mi40LDE1LjMtMTE5LjVjLTcuMi0xMS42LTE3LTIxLjUtMjguNi0yOC45YzIxLjUtMjAuOCwzMy4zLTQ5LjgsNTYuNC02OS4xYzUuNi00LjIsMTIuOC01LjQsMTkuNi01LjIKCQkJYzYuMS0yLjIsNC40LTkuOCw0LjUtMTQuOFYxLjFjLTE2LjYtMS41LTM0LjcsMC44LTQ3LjcsMTIuMmMtMjcuNywyMS0zOS43LDU2LTY2LjYsNzcuN2MtMTMuNCw5LjYtMzMuMSw3LjEtNDQuNy00LjYKCQkJQzg1LjksNjQuMSw3My42LDMxLjksNDcuMSwxMi42QzM1LDIuOSwxOS4zLDAuOSw0LjQsMEw0LjQsMHogTTEzNiwxMzUuNmMzMi45LDAuMSw2MSwzMy41LDU1LjEsNjZjLTMuOSwyOC42LTMyLjIsNTEuOS02MS4yLDQ4LjkKCQkJYy0yNS41LTIuMi00OC45LTIzLjItNTIuMi00OS4xYy0zLjYtMjIuNiw3LjYtNDcuMSwyOC4xLTU4QzExNC45LDEzOC4yLDEyNS40LDEzNS41LDEzNiwxMzUuNkwxMzYsMTM1LjZ6Ii8+Cgk8L2c+CjwvZz4KPC9zdmc+";
const char* SIGNS_GEMAUX_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjY4LjMgMjg5LjQiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDI2OC4zIDI4OS40OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzY2Q0MzMzt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxNzMiIGNsYXNzPSJzdDAiIGQ9Ik0xMy40LDBDNS42LDAuMiwyLjQsOSwxLjYsMTUuNUMwLDIyLjEtMi4xLDMxLjQsNC43LDM1LjhjMTYuMyw1LjksMzQsNi41LDUwLjksMTAKCQkJYzAuMSw2NS4yLDAuMiwxMzAuNCwwLjEsMTk1LjZjLTE2LjcsMi43LTM0LDQuMS01MCw5LjZjLTcuNCw0LjgtNS43LDE1LTMuOCwyMi4zYzEuMiw1LjQsMi41LDEwLjcsMy43LDE2LjEKCQkJYzgwLjItMTcuNywxNjQtMTksMjQ0LjUtMi42YzQuMywwLjgsOC41LDEuNywxMi44LDIuNmMwLjctMTEuMSw3LjctMjIsNC40LTMzLjFjLTQuMS04LjMtMTQuOS04LTIyLjYtOS43CgkJCWMtMTAuNS0xLjktMjEuMS0zLjUtMzEuNy01YzAtNjUuMy0wLjYtMTMwLjYsMC0xOTUuOGMxNi44LTMsMzQuNC00LjEsNTAuNi05LjhjNi44LTQuNiw0LjYtMTQsMy4yLTIwLjhjLTAuNy02LjgtNS0xNS41LTEzLTE0LjkKCQkJYy0xNi4xLDEuNC0zMS42LDYuMi00Ny42LDcuM0MxNDIuOSwxNS4zLDc4LjUsMTIuMywxNiwwLjFDMTUuMSwwLDE0LjMsMCwxMy40LDBMMTMuNCwweiBNMTczLjksMTQzLjZsMC4yLDk0LjEKCQkJYy0yNi40LTEuMS01Mi44LTEuMS03OS4yLDB2LTE4OGMyNi4yLDEuNCw1Mi42LDAuOSw3OC44LTAuMkwxNzMuOSwxNDMuNkwxNzMuOSwxNDMuNnoiLz4KCTwvZz4KPC9nPgo8L3N2Zz4=";
const char* SIGNS_CANCER_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMzAwLjMgMjA2LjYiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDMwMC4zIDIwNi42OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzAwMzNGRjt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxOTUiIGNsYXNzPSJzdDAiIGQ9Ik0xNTAuMiwwQzExMS44LDAuNyw3MS41LDQuNywzNy44LDI0LjdDMTUuNywzOC4zLTEsNjMuMSwwLjgsODkuOAoJCQljMS40LDMyLjgsMjcuNSw2My43LDYwLjcsNjcuNWMyNC43LDQuMiw1Mi40LTYuMiw2NS4yLTI4LjVjMTUuNi0yNS42LDExLjgtNTkuNS00LjUtODMuOWMtMS4yLTIuMy01LTUuNiwwLTQuOAoJCQljNDIuNS0zLjgsODUuMy0wLjksMTI3LjcsMi44YzEzLjYsMS4xLDI3LjIsMy4zLDQwLjcsMy42YzguMy0yLDEwLjgtMTIuMyw5LjMtMTkuN2MwLjctNC41LDEuNy0xMS44LTQuMi0xMy4zCgkJCUMyNDcuNSw1LjcsMTk5LTAuNSwxNTAuMiwwTDE1MC4yLDB6IE0yMjkuMSw0OS4xYy0zMi45LDEtNjMuOSwyNy42LTY3LjksNjAuNmMtMS44LDIwLjMsNy42LDM5LjgsMTkuNiw1NS42CgkJCWMtNTQuMSw1LjktMTA4LjYsMC40LTE2Mi41LTUuNGMtNS45LTAuNS0xMy4xLTAuMS0xNi4yLDUuOWMtMy4yLDQuOC0yLjEsMTAuNi0xLjgsMTUuOWMtMC44LDQuNSwwLjUsMTEsNi4xLDExLjEKCQkJYzUxLDguMywxMDIuNiwxNSwxNTQuNCwxMy42YzM3LjUtMS43LDc2LjUtOC43LDEwOC0zMC40YzE4LTEyLjgsMzEuNi0zMy42LDMwLjktNTYuMmMwLjEtMzEuNy0yMi44LTYyLjktNTQuNC02OS4xCgkJCUMyNDAuMSw0OS41LDIzNC42LDQ4LjksMjI5LjEsNDkuMUwyMjkuMSw0OS4xeiBNNzQuNyw1MS42YzcuOCw3LjIsMTQuMiwxNS43LDE5LDI1LjFjNC43LDkuOSw3LjYsMjMuOS0xLDMyLjcKCQkJYy04LjMsOC0yMC44LDExLjUtMzIsOS44Yy04LjgtMS41LTE2LjEtOC43LTE2LjktMTcuN0M0MCw4MC42LDU0LjcsNjAuMiw3My40LDUyLjJDNzMuOCw1MS45LDc0LjIsNTEuNyw3NC43LDUxLjZMNzQuNyw1MS42egoJCQkgTTIzMS42LDg3LjNjMTQuMi0wLjQsMjguOSwxMi41LDI2LjgsMjcuNWMtMS44LDE4LjMtMTYuOSwzMi45LTMzLjIsMzkuNmMtMy4zLTIuMi01LjItNi4zLTguMi04LjljLTguNS0xMC0xOC4xLTIyLjgtMTQuOC0zNi43CgkJCUMyMDUuNSw5Ni4yLDIxOC40LDg2LjcsMjMxLjYsODcuM0wyMzEuNiw4Ny4zeiIvPgoJPC9nPgo8L2c+Cjwvc3ZnPg==";
const char* SIGNS_LION_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjE5LjQgMjg3LjUiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDIxOS40IDI4Ny41OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6I0ZGMDAwMDt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxOTkiIGNsYXNzPSJzdDAiIGQ9Ik0xMzAuOCwwQzg4LDAuMSw0Ny4zLDM1LjQsNDMuOCw3OC42Yy0xLjIsMTEuMywwLjYsMjIuOCwzLjUsMzMuOAoJCQlDMjAuNiwxMTgsMC41LDE0My41LDAuMSwxNzAuNWMtMS4yLDI0LjcsMTMuNCw0OS45LDM2LjUsNTkuNWMyMi4xLDEwLjIsNTAuNSw2LjUsNjcuOC0xMS4xYzIxLjYtMjAuMywyNy4yLTU2LjcsOS41LTgxLjMKCQkJYy04LjEtMTEuOC0yMi44LTE4LjYtMjcuMy0zMi45Yy04LjUtMjIsMS4xLTUwLjMsMjMuMS02MC4zYzE5LjItOS41LDQ0LjItNCw1Ny43LDEyLjRjMTAuNCwxMS45LDEzLjksMjkuNyw3LDQ0LjIKCQkJYy04LjYsMjAuNS0yNi4xLDM1LjYtMzUuMyw1NS43Yy0xNC45LDI4LjYtMjMsNjIuOC0xMy43LDk0LjRjNS44LDE4LjQsMjEuOCwzNC44LDQxLjgsMzYuMWMxNy44LDEuNiwzNS41LTMuNSw0OS44LTE0LjMKCQkJYzQuNy01LjMsMi4xLTEzLjItMS44LTE4LjFjLTMuMi02LjItNy43LTE0LjQtMTUuOC0xNGMtMTAuMiwxLjUtMTkuNywxMC40LTMwLjEsNi4xYy04LjktNS40LTktMTcuNS04LjUtMjYuNwoJCQljMi4xLTI4LjgsMTcuNy01NS4yLDM1LjQtNzcuNmMxNS42LTIyLjQsMjYtNTAuOSwxOS03OC4yQzIwNS41LDI3LjUsMTY5LjEtMSwxMzAuOCwwTDEzMC44LDB6IE02Mi42LDE1MAoJCQljMTUuNS0wLjIsMjcuMywxOC4yLDIwLjUsMzIuM2MtNS41LDEyLjctMjMuNSwxOC4xLTM0LjUsOWMtMTAuNS03LjUtMTIuNi0yNC41LTMtMzMuNkM0OS45LDE1Mi44LDU2LjEsMTUwLDYyLjYsMTUwTDYyLjYsMTUweiIvPgoJPC9nPgo8L2c+Cjwvc3ZnPg==";
const char* SIGNS_VIERGE_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjU2LjEgMzEyLjQiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDI1Ni4xIDMxMi40OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6Izk5NjYzMzt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxODMiIGNsYXNzPSJzdDAiIGQ9Ik0xMi40LDBDMy44LTAuMS0wLjcsOS42LDAuMSwxNy4yQzAsMjQuMywxLjYsMzIuOSw4LjYsMzYuNEMxNiw1Mi43LDE1LjEsNzAuNywxNyw4OC4yCgkJCWMzLDQ5LjksMi42LDEwMC4xLDIuMiwxNTAuMWMtMS4yLDUuMyw0LjksOC44LDkuNSw3LjNjOS4zLTAuMywxOC43LDAuMSwyOC0wLjFjLTAuNC00NC4zLTAuNy04OC42LTEuMS0xMzIuOQoJCQljNy45LTIwLjEsMTUuMy00MC40LDI0LjMtNjBjNS45LDM4LjEsNS42LDc2LjcsNi45LDExNS4xYzAuNSwyNS45LDAuNyw1MS45LDEuMSw3Ny44aDM2LjhjLTAuNi00NC0xLjEtODguMS0yLjktMTMyLjEKCQkJYzguMi0yMC43LDE1LjktNDEuOCwyNS40LTYxLjljNS41LDM2LjUsNS4xLDczLjcsNi4xLDExMC42YzAuNCwyOC4yLDAuNCw1Ni41LDEuMSw4NC43Yy0xNC4yLDguMy0zMC4yLDEzLTQ1LjksMTgKCQkJYzQuMyw5LjcsMi42LDIyLjgsMTEuNywzMGM4LjMsNC44LDE3LjQtMS40LDI1LjUtMy42YzYtMi4zLDExLjktNSwxNy45LTcuNWM3LjEsMTIuMSwxNy40LDIzLjIsMzAuNiwyOC41CgkJCWM4LjgsMS4zLDE0LjYtNy4zLDE3LjQtMTQuNGMyLjEtNCw1LjktNy44LDUuNy0xMi42Yy04LjUtNS44LTE4LjEtMTEuOS0yMi4xLTIxLjljNDIuMy0zNiw2Ni44LTkzLjQsNTkuNi0xNDkKCQkJYy0yLjQtMTYtOC41LTMzLjMtMjIuNS00Mi43Yy0xMS44LTcuNS0yNy42LTYuMS0zOC43LDJjLTIuNywxLjgtNS4zLDMuNy03LjcsNS45Yy0yLjUtMjIuOC00LjQtNDctMTctNjYuOAoJCQljLTYuMy04LjgtMTkuNi0xMy4xLTI4LjktNi44Yy0xMyw3LTIwLjEsMjEuNC0yNi45LDMzLjJjLTMtMTMuMS04LTI4LjEtMjAuOS0zNC42QzgxLTAuMiw2OC40LDYuNCw2MS43LDE1LjUKCQkJQzU2LDIyLDUxLjYsMjkuNyw0Ny41LDM3LjJjLTMuNi0xNC43LTExLjMtMzEtMjYuNy0zNi4xQzE4LjEsMC4zLDE1LjMtMC4xLDEyLjQsMEwxMi40LDB6IE0yMTMuOCwxMDQuN2M0LjksNy41LDQuOSwxNyw1LjYsMjUuNwoJCQljMC44LDMwLjUtMTAuOCw2MC4xLTI4LjUsODQuNmMtMC40LTI1LjUtMC41LTUxLjEtMC44LTc2LjZDMTk2LjgsMTI2LjMsMjAyLjIsMTEyLjcsMjEzLjgsMTA0LjdMMjEzLjgsMTA0Ljd6Ii8+Cgk8L2c+CjwvZz4KPC9zdmc+";
const char* SIGNS_BALANCE_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMzExIDIzNi42IiBzdHlsZT0iZW5hYmxlLWJhY2tncm91bmQ6bmV3IDAgMCAzMTEgMjM2LjY7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDojNjZDQzMzO30KPC9zdHlsZT4KPGcgaWQ9ImxheWVyMSI+Cgk8ZyBpZD0iZzQzMjIiPgoJCTxwYXRoIGlkPSJwYXRoNDE4MSIgY2xhc3M9InN0MCIgZD0iTTE1My42LDBDMTAzLjgsMCw1NC44LDM1LjYsNDMuMiw4NC43Yy01LjMsMjIuOSwwLjEsNDguNSwxNS44LDY2LjIKCQkJYy0xNy4yLDEuMi0zNC43LDAuOS01MS41LDQuNmMtOCwzLjktNy43LDE0LjQtNy4zLDIyYzAsNy43LDcuMywxNS4xLDE1LjEsMTIuOGM0My4zLTMuMiw4Ni43LTQuNiwxMzAtNS4yYzUtMy4zLDEuMy0xMC4yLDIuNS0xNQoJCQl2LTE5LjVjLTE2LjctMy42LTM1LjUtMi44LTQ5LjUtMTQuMmMtMTMuMy05LjYtMTguOC0yNy4yLTE1LjctNDMuMWM0LjYtMjksMzAuNy01Mi4yLDU5LjMtNTZjMjcuNy00LjgsNTkuMiw1LjYsNzUuNCwyOS43CgkJCWMxMi4xLDE3LjEsMTYsNDEuNSw0LjUsNTkuOGMtMTAuNywxNi41LTMxLjMsMjAuOC00OS44LDIyLjNjLTQsMC4xLTguNSwyLjItOC41LDYuOGMwLjUsOS43LDAsMTkuNSwwLjIsMjkuMwoJCQljNDkuMiwwLjYsOTguNCwxLjYsMTQ3LjMsNi41bC0xLjItMzdjLTIwLjMtMS00MC40LTMuMi02MC43LTQuMWMyMC4xLTI2LjcsMjIuOS02NS4yLDYuNS05NC40QzIzNy4xLDIxLjUsMTk4LjIsMC40LDE1OS40LDAKCQkJQzE1Ny41LTAuMSwxNTUuNi0wLjEsMTUzLjYsMEwxNTMuNiwweiBNMTIwLjgsMTk2Yy0zNy40LDAuMi03NC44LDIuMS0xMTIuMSw0LjljLTUuNCwxLjMtNy4yLDcuNi01LjksMTIuNQoJCQljMC40LDcuNy0wLjEsMTUuNSwwLjEsMjMuMmMzNy40LTAuMyw3NC42LTQuMSwxMTItNC4xYzYwLjctMS4zLDEyMS41LDAuNiwxODIsNGM4LjQtMS4xLDEyLjEtMTAuOCwxMC43LTE4LjNjMC01LjQsMC0xMC45LDAtMTYuMwoJCQljLTUzLjctNi4yLTEwNy45LTUuMi0xNjEuOC02QzEzNy41LDE5NS45LDEyOS4yLDE5NS45LDEyMC44LDE5NkwxMjAuOCwxOTZ6Ii8+Cgk8L2c+CjwvZz4KPC9zdmc+";
const char* SIGNS_SCORPION_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjk0LjQgMzIzLjMiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDI5NC40IDMyMy4zOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzAwMzNGRjt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxODUiIGNsYXNzPSJzdDAiIGQ9Ik0wLjEsMS45QzAuOSwxMi4xLTEuMSwyMi41LDEsMzIuNWMxLjQsNC42LDUuMyw4LjEsMTAuMSw4LjhjMi43LDUuMywzLjQsMTEuNSw0LjcsMTcuMwoJCQljNC4xLDI1LjgsNCw1Miw1LDc4LjFjMC45LDM3LjgsMC43LDc1LjYsMS4yLDExMy40aDM4LjljMC4xLTQ0LjItMC41LTg4LjQtMS4zLTEzMi41QzY5LjIsOTYsNzguMSw3NCw4OS4zLDUzLjIKCQkJYzYuNywzMy41LDcsNjcuOCw4LjQsMTAxLjhjMC45LDMxLjcsMC44LDYzLjQsMC44LDk1LjFoMzkuMmMtMC4xLTQ0LTEtODguMS0zLjItMTMyLjFjOS45LTIyLjIsMTguOC00NC45LDMwLjgtNjYKCQkJYzcuOSw0Myw3LjIsODcsOC40LDEzMC42YzAuMiwyNi44LTEuNCw1NC4yLDUuNSw4MC41YzQuNCwxNC41LDE1LjQsMjcuMywzMC4yLDMxLjdjOC44LDMuMiwxOC4yLDQuNiwyNy41LDUuNnYyMi45CgkJCWMxOC4yLTExLjcsMzcuOS0yMSw1NS4yLTMzLjljNS41LTYuOCwwLjMtMTcuMi03LjItMjAuMWMtMTUuNC05LjgtMzEuNC0xOC42LTQ2LjktMjguMWwtMC43LDIwYy03LjUtMC42LTE3LjktMi41LTE5LjctMTEuMwoJCQljLTYuNi0yMy4xLTQuMi00Ny4zLTUuNi03MC45Yy0xLjMtNDcuOS0xLjktOTYuNS0xMy40LTE0My4zYy0zLjMtMTEuOS04LjctMjUtMjAuMi0zMWMtMTAuNy00LjctMjMuMiwwLjUtMzAuNCw5LjEKCQkJYy05LjMsOS4yLTE2LDIwLjctMjIuMywzMi4xYy0yLjktMTMuOS02LjgtMzAtMTkuOS0zNy45Yy0xMi4xLTYuNC0yNy40LTEuMi0zNS43LDljLTcuNCw3LjgtMTMuMSwxNy0xOC4yLDI2LjMKCQkJYy0zLjgtMTUuOC0xMi4yLTMzLTI4LjQtMzguOUMxNiwxLjcsNy44LDEuOCwwLjEsMEMwLjEsMCwwLjEsMS45LDAuMSwxLjl6Ii8+Cgk8L2c+CjwvZz4KPC9zdmc+";
const char* SIGNS_SAGITTAIRE_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMzE3LjEgMzE2LjUiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDMxNy4xIDMxNi41OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6I0ZGMDAwMDt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxNjEiIGNsYXNzPSJzdDAiIGQ9Ik0xNDcuMywwYy01LjItMC4xLTUuOCw2LTUuNyw5LjljLTAuOSw4LjgtNCwxOC45LDEuNiwyNi45YzMyLjYsNS4yLDY1LjUsOC4yLDk4LjIsMTIuNAoJCQljLTQxLjIsNDEtODIuMyw4Mi4xLTEyMy40LDEyMy4xbC01Ny4zLTU3LjNjLTguNyw4LjgtMTcuNCwxNy42LTI2LjEsMjYuNGw1Ny4xLDU3LjFMMCwyOTAuMmwyNi4xLDI2LjRsOTEuNy05MS43bDU3LjUsNTcuNQoJCQlsMjYuMy0yNi4xYy0xOS4xLTE5LjItMzguNC0zOC4yLTU3LjMtNTcuNmM0MC44LTQxLjMsODEuOC04Mi40LDEyMy4xLTEyMy4yYzQuMiwzMi43LDcuMyw2NS43LDEyLjMsOTguMwoJCQljMi45LDUuOSwxMC4zLDMuNSwxNS4zLDIuOGwyMi0yLjJjLTcuNy01MS42LTEyLjQtMTAzLjYtMTkuMy0xNTUuNGMtNDkuMy02LjctOTktMTEtMTQ4LjEtMTguNUMxNDguOSwwLjEsMTQ4LjEsMCwxNDcuMywwCgkJCUwxNDcuMywweiIvPgoJPC9nPgo8L2c+Cjwvc3ZnPg==";
const char* SIGNS_CAPRICORNE_SVG = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMzEwLjggMzExLjkiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDMxMC44IDMxMS45OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6Izk5NjYzMzt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxNTkiIGNsYXNzPSJzdDAiIGQ9Ik0xNDcuOCwwYy0xNi43LDAuNS0yOS4xLDE0LTM4LjQsMjYuNWMtOS40LDEyLjctMTYuOCwyNi44LTI0LDQwLjhDNzUuMiw0MCw1NS42LDE0LjMsMjcuMyw0LjQKCQkJQzIwLjksMS42LDExLjEsMC41LDcsNy42Yy00LjYsNy41LTMuOSwxNi44LTcsMjQuOGMwLjEsNS45LDcuNCw2LjQsMTEuOCw2LjljMTcuNSwyLjgsMjguNiwxOSwzNC45LDM0LjIKCQkJYzE1LDM1LjUsMTYsNzUuMSwxNy45LDExMy4yYzEyLjMtMi4xLDI0LjktMi45LDM3LjQtMi4zYy0wLjgtMTgtMS41LTM2LTMuMS01My45YzEzLjMtMzAuNywyNC4yLTYzLjEsNDQuOC04OS45CgkJCWMxLjgtMi45LDMuMi0wLjIsNC4yLDJjNi4xLDEyLjksNy40LDI3LjcsMTAuMSw0MS43YzUuMiwzNC4xLDguMyw2OC42LDkuMywxMDMuMWMtMC4xLDIzLjUtNCw0OS40LTIxLjQsNjYuOAoJCQljLTEzLjEsMTIuOC0zMSwxOC00OC4zLDIyLjVjLTUuNiwyLjItNy42LDguOS01LjgsMTQuMmMxLDcuMywxLjgsMTcuMyw5LjksMjAuMWM5LjQsMi45LDE4LjgtMS45LDI3LjctNC40CgkJCWMyNy42LTkuNSw1My0yOSw2NC01Ni43YzIuMy01LjMsNC0xMC44LDUuOS0xNi4yYzI3LjUsMTguNiw2Ny45LDE1LDkwLjktOS4yYzIzLjQtMjMuNywyNy45LTY0LjIsOC4xLTkxLjUKCQkJYy0xOC40LTI2LjgtNTYtMzguNC04Ni4yLTI1LjljLTQuNCwxLjgtOC42LDQtMTIuNSw2LjZjLTQtMzIuMi03LjctNjUuNS0yMy4zLTk0LjVDMTcwLjIsOS4xLDE2MC4yLTAuMywxNDcuOCwwTDE0Ny44LDB6CgkJCSBNMjM5LjYsMTM5LjhjMTkuMiwwLDM2LjMsMTguNywzMy4zLDM4Yy0yLDE3LjYtMTkuMywzMi42LTM3LjQsMzAuMmMtMjEtMS45LTM2LjgtMjYuMi0yOC41LTQ2QzIxMiwxNDguOCwyMjUuMiwxMzksMjM5LjYsMTM5LjgKCQkJTDIzOS42LDEzOS44eiIvPgoJPC9nPgo8L2c+Cjwvc3ZnPg==";
const char* SIGNS_VERSEAU_SVG  = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjkxLjMgMjA4LjYiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDI5MS4zIDIwOC42OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzY2Q0MzMzt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxNzEiIGNsYXNzPSJzdDAiIGQ9Ik05MS45LDFDNjMuMiwyMC4xLDMzLDM2LjksNS41LDU3LjdjLTUuNCw1LjItNi44LDE0LjctMS4zLDIwLjRjMy4yLDYsOS43LDEyLjIsMTcsOS40CgkJCWMxMS41LTMuNCwyMC4yLTEyLjEsMzAuNS0xNy43QzYwLjQsNjQuMiw2OS4yLDU4LjYsNzgsNTNjNi41LDEyLjgsMTAuNiwyNy4yLDIwLDM4LjNjNi42LDQuOSwxNC44LDAuMSwxOS45LTQuNgoJCQljMTQuOS0xMC42LDI5LjYtMjEuNCw0NC40LTMyYzYuNCwxNS40LDEyLjUsMzAuOSwxOC44LDQ2LjRDMjAyLDg1LjMsMjIzLjMsNjkuOCwyNDQuOSw1NWM0LjIsOS41LDYuMiwyMS4xLDE0LjUsMjguMgoJCQljNyw0LjQsMTUuMiwwLjEsMjEuOC0zYzMuOS0xLjIsOC4xLTIuOCwxMC4yLTYuNmMtOS40LTIxLjctMTYuNi00NC41LTI3LjctNjUuNGMtNi4yLTUuOS0xNS42LTEuOC0yMSwzLjMKCQkJYy0xNS4zLDEwLjgtMzAuMywyMi00NS42LDMyLjhjLTUuNS0xMi04LjItMjUuNy0xNi44LTM2Yy02LjQtNS4xLTE1LjQtMS45LTIwLjUsMy41Yy0xNS4zLDExLTMwLjUsMjIuMS00NS44LDMzLjEKCQkJQzEwNy4xLDI5LjksMTAwLjMsMTUsOTMuNSwwTDkxLjksMUw5MS45LDF6IE0yNjAsMTE4LjJjLTE0LjksNC42LTI2LjIsMTYtMzguOSwyNC40Yy04LDUuOC0xNiwxMS42LTI0LjEsMTcuMgoJCQljLTUuNS0xMi4yLTguNy0yNS45LTE3LjItMzYuNmMtNS43LTQuOC0xNC0xLjYtMTguNiwzLjJjLTE1LjgsMTEuMy0zMS40LDIyLjctNDcuMiwzNGMtNi41LTEyLjYtMTAuNy0yNi43LTE5LjItMzguMQoJCQljLTMuNi0zLjUtOS43LTIuOC0xMi45LDAuOWMtMjYuNSwxNy01My42LDMzLjQtNzkuNCw1MS40Yy01LjUsNi45LTAuNywxNi4zLDQuMiwyMi4xYzIuNiwzLjksNC43LDExLjUsMTAuOCwxMC41CgkJCWM0LjMtMS40LDcuMS01LjQsMTEuMy03LjFjMTYuNC0xMC41LDMyLjctMjEuMSw0OS4yLTMxLjVjNS45LDExLjQsOC44LDI0LjUsMTcsMzQuNmM3LjIsNi42LDE4LjIsMy42LDI1LTIKCQkJYzEyLjQtOC43LDI0LjItMTguMiwzNi42LTI2LjdjMS45LTEuNSwzLjktMi44LDUuOS0zLjljNS4xLDExLjYsOC40LDI0LjIsMTUuNCwzNC45YzYuMiw1LjksMTUuOSwyLjQsMjEuNS0yLjcKCQkJYzE1LjMtMTAuNSwzMC4xLTIyLDQ1LjQtMzIuM2M0LjMsOS42LDYuNiwyMSwxNC4zLDI4LjZjNy44LDQuOCwxNi43LTEsMjMuNy00LjZjNi4yLTQuMyw2LjktMTMuNCwyLjctMTkuMwoJCQljLTcuOS0xOS4yLTE0LjgtMzguOS0yNC4yLTU3LjRsLTAuOCwwLjNMMjYwLDExOC4yTDI2MCwxMTguMnoiLz4KCTwvZz4KPC9nPgo8L3N2Zz4=";
const char* SIGNS_POISSON_SVG  = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMjQwLjYgMzE5LjciIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDI0MC42IDMxOS43OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzAwMzNGRjt9Cjwvc3R5bGU+CjxnIGlkPSJsYXllcjEiPgoJPGcgaWQ9Imc0MzIyIj4KCQk8cGF0aCBpZD0icGF0aDQxNjMiIGNsYXNzPSJzdDAiIGQ9Ik0yMTIuMywxLjJjLTM1LjksMzctNjEuNCw4NS40LTY2LjIsMTM3LjFjMC45LDUuOC03LjEsMi0xMC42LDMuMWwtNDEuNC0wLjIKCQkJQzg5LjgsOTEuNCw2NC41LDM1LjUsMjksMC4zQzE3LjUsOS42LDEwLjEsMTUuOCwwLDI1LjRDMzEsNTQsNTAuOSw5My44LDU3LjUsMTM1LjNjMC42LDMuNiwxLjgsOC0zLjcsNi4yCgkJCWMtMTQuNywwLTI5LjUsMC4yLTQ0LjEsMnYzNC44aDQ4LjVjLTMuNiwzNi40LTE5LjQsNzEuMS00Mi4zLDk5LjRjLTUsNS45LTEwLjQsMTEuNi0xNS43LDE3LjNsMjYuNSwyNC44CgkJCWMzNy44LTM3LjMsNjMuNS04Ny43LDY3LjQtMTQxLjFsNTEuOC0wLjNjMy4yLDUwLjksMjguMyw5OC40LDYyLjIsMTM1LjdjMi45LDQsNS45LDcuNyw5LjMsMS45bDIzLjItMjEuMgoJCQljLTMxLjctMjktNTIuMS03MC01OC4xLTExMi4zYy0yLjYtNS43LDMtNC4yLDYuOC00LjJoNDEuMnYtMzQuN2MtMTYtMi0zMi4zLTIuMS00OC40LTJjMy44LTM3LjEsMjAuMi03Mi43LDQ0LTEwMS4zCgkJCWM0LjQtNS4yLDkuMS0xMC4yLDEzLjgtMTUuMkwyMTMuNCwwTDIxMi4zLDEuMnoiLz4KCTwvZz4KPC9nPgo8L3N2Zz4=";

string Sign::read_svg(int sign) {
    string r = "data:image/svg+xml;base64,";
    switch (sign) {
        case SIGNS_BELIER:
            return r + SIGNS_BELIER_SVG;
        case SIGNS_TAUREAU:
            return r + SIGNS_TAUREAU_SVG;
        case SIGNS_GEMAUX:
            return r + SIGNS_GEMAUX_SVG;
        case SIGNS_CANCER:
            return r + SIGNS_CANCER_SVG;
        case SIGNS_LION:
            return r + SIGNS_LION_SVG;
        case SIGNS_VIERGE:
            return r + SIGNS_VIERGE_SVG;
        case SIGNS_BALANCE:
            return r + SIGNS_BALANCE_SVG;
        case SIGNS_SCORPION:
            return r + SIGNS_SCORPION_SVG;
        case SIGNS_SAGITTAIRE:
            return r + SIGNS_SAGITTAIRE_SVG;
        case SIGNS_CAPRICORNE:
            return r + SIGNS_CAPRICORNE_SVG;
        case SIGNS_VERSEAU:
            return r + SIGNS_VERSEAU_SVG;
        case SIGNS_POISSON:
            return r + SIGNS_POISSON_SVG;
        default:
            return "";
    }
}

const char* Sign::read_svg_c(int sign) {
    switch (sign) {
        case SIGNS_BELIER:
            return SIGNS_BELIER_SVG;
        case SIGNS_TAUREAU:
            return SIGNS_TAUREAU_SVG;
        case SIGNS_GEMAUX:
            return SIGNS_GEMAUX_SVG;
        case SIGNS_CANCER:
            return SIGNS_CANCER_SVG;
        case SIGNS_LION:
            return SIGNS_LION_SVG;
        case SIGNS_VIERGE:
            return SIGNS_VIERGE_SVG;
        case SIGNS_BALANCE:
            return SIGNS_BALANCE_SVG;
        case SIGNS_SCORPION:
            return SIGNS_SCORPION_SVG;
        case SIGNS_SAGITTAIRE:
            return SIGNS_SAGITTAIRE_SVG;
        case SIGNS_CAPRICORNE:
            return SIGNS_CAPRICORNE_SVG;
        case SIGNS_VERSEAU:
            return SIGNS_VERSEAU_SVG;
        case SIGNS_POISSON:
            return SIGNS_POISSON_SVG;
        default:
            return "";
    }
}

string Sign::nom(int sign) {
    switch (sign) {
        case SIGNS_BELIER:
            return "Belier";
        case SIGNS_TAUREAU:
            return "Taureau";
        case SIGNS_GEMAUX:
            return "Gemaux";
        case SIGNS_CANCER:
            return "Cancer";
        case SIGNS_LION:
            return "Lion";
        case SIGNS_VIERGE:
            return "Vierge";
        case SIGNS_BALANCE:
            return "Balance";
        case SIGNS_SCORPION:
            return "Scorpion";
        case SIGNS_SAGITTAIRE:
            return "Sagittaire";
        case SIGNS_CAPRICORNE:
            return "Capricorne";
        case SIGNS_VERSEAU:
            return "Verseau";
        case SIGNS_POISSON:
            return "Poisson";
        default:
            cerr << "Unreachable code reached" << endl;
            return "";
    }
}
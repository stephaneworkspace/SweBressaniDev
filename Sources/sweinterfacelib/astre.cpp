//
// Created by Stéphane on 21.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

string Astre::read_svg(Astres astre) {
    string* a = new string[14];
    a[0] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIKCSBpZD0ic3ZnOSIgaW5rc2NhcGU6dmVyc2lvbj0iMC45Mi41ICgyMDYwZWMxZjlmLCAyMDIwLTA0LTA4KSIgc29kaXBvZGk6ZG9jbmFtZT0iRWFydGhfc3ltYm9sLnN2ZyIgeG1sbnM6Y2M9Imh0dHA6Ly9jcmVhdGl2ZWNvbW1vbnMub3JnL25zIyIgeG1sbnM6ZGM9Imh0dHA6Ly9wdXJsLm9yZy9kYy9lbGVtZW50cy8xLjEvIiB4bWxuczppbmtzY2FwZT0iaHR0cDovL3d3dy5pbmtzY2FwZS5vcmcvbmFtZXNwYWNlcy9pbmtzY2FwZSIgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIiB4bWxuczpzb2RpcG9kaT0iaHR0cDovL3NvZGlwb2RpLnNvdXJjZWZvcmdlLm5ldC9EVEQvc29kaXBvZGktMC5kdGQiIHhtbG5zOnN2Zz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciCgkgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgeD0iMHB4IiB5PSIwcHgiIHZpZXdCb3g9IjAgMCAxMiAxMiIKCSBzdHlsZT0iZW5hYmxlLWJhY2tncm91bmQ6bmV3IDAgMCAxMiAxMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtkaXNwbGF5Om5vbmU7ZmlsbDpub25lO30KCS5zdDF7ZmlsbDpub25lO3N0cm9rZTojRjE4NzAwO3N0cm9rZS13aWR0aDowLjc1O3N0cm9rZS1taXRlcmxpbWl0OjEwO30KCS5zdDJ7ZmlsbDojRjE4NzAwO30KPC9zdHlsZT4KPHNvZGlwb2RpOm5hbWVkdmlldyAgYm9yZGVyY29sb3I9IiM2NjY2NjYiIGJvcmRlcm9wYWNpdHk9IjEiIGdyaWR0b2xlcmFuY2U9IjEwIiBndWlkZXRvbGVyYW5jZT0iMTAiIGlkPSJuYW1lZHZpZXcxMSIgaW5rc2NhcGU6Y3VycmVudC1sYXllcj0ic3ZnOSIgaW5rc2NhcGU6Y3g9IjcuODgxMzU1NCIgaW5rc2NhcGU6Y3k9IjgiIGlua3NjYXBlOm9iamVjdC1wYXRocz0idHJ1ZSIgaW5rc2NhcGU6cGFnZW9wYWNpdHk9IjAiIGlua3NjYXBlOnBhZ2VzaGFkb3c9IjIiIGlua3NjYXBlOnNuYXAtaW50ZXJzZWN0aW9uLXBhdGhzPSJ0cnVlIiBpbmtzY2FwZTpzbmFwLW1pZHBvaW50cz0idHJ1ZSIgaW5rc2NhcGU6c25hcC1vYmplY3QtbWlkcG9pbnRzPSJ0cnVlIiBpbmtzY2FwZTpzbmFwLXNtb290aC1ub2Rlcz0idHJ1ZSIgaW5rc2NhcGU6d2luZG93LWhlaWdodD0iMTAxNSIgaW5rc2NhcGU6d2luZG93LW1heGltaXplZD0iMSIgaW5rc2NhcGU6d2luZG93LXdpZHRoPSIxOTIwIiBpbmtzY2FwZTp3aW5kb3cteD0iMCIgaW5rc2NhcGU6d2luZG93LXk9IjAiIGlua3NjYXBlOnpvb209IjU5IiBvYmplY3R0b2xlcmFuY2U9IjEwIiBwYWdlY29sb3I9IiNmZmZmZmYiIHNob3dncmlkPSJmYWxzZSI+Cgk8L3NvZGlwb2RpOm5hbWVkdmlldz4KPGcgaWQ9Imc4MjMiPgoJPHBhdGggaWQ9InBhdGg2IiBpbmtzY2FwZTpjb25uZWN0b3ItY3VydmF0dXJlPSIwIiBzb2RpcG9kaTpub2RldHlwZXM9ImNjIiBjbGFzcz0ic3QwIiBkPSJNMiw2aDgiLz4KCTxwYXRoIGlkPSJwYXRoMi01IiBpbmtzY2FwZTpjb25uZWN0b3ItY3VydmF0dXJlPSIwIiBjbGFzcz0ic3QxIiBkPSJNMTAsNmMwLTIuMi0xLjgtNC00LTRTMiwzLjgsMiw2czEuOCw0LDQsNFMxMCw4LjIsMTAsNnoiLz4KCTxwYXRoIGlkPSJwYXRoMiIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgY2xhc3M9InN0MiIgZD0iTTYuOSw2YzAtMC41LTAuNC0wLjktMC45LTAuOVM1LjEsNS41LDUuMSw2UzUuNSw2LjksNiw2LjkKCQlTNi45LDYuNSw2LjksNiIvPgo8L2c+Cjwvc3ZnPg==";
    a[1] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6I0JDQjE5QTtzdHJva2Utd2lkdGg6MztzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0zNyw0QzI1LjQsMC40LDEzLjEsNi44LDkuNCwxOC40UzEyLjMsNDIuNCwyMy45LDQ2YzQuMywxLjMsOC44LDEuMywxMy4xLDBjLTExLjYtMy42LTE4LjEtMTYtMTQuNC0yNy42CglDMjQuNywxMS41LDMwLjEsNi4yLDM3LDR6Ii8+Cjwvc3ZnPg==";
    a[2] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgMTIgMTIiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDEyIDEyOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6IzY0NEM5OTtzdHJva2Utd2lkdGg6MC43NTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxnIGlkPSJzdXJmYWNlMSI+Cgk8cGF0aCBjbGFzcz0ic3QwIiBkPSJNOCw1YzAtMS4xLTAuOS0yLTItMlM0LDMuOSw0LDVzMC45LDIsMiwyUzgsNi4xLDgsNXoiLz4KCTxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik00LDFjMCwxLjEsMC45LDIsMiwyczItMC45LDItMiIvPgoJPHBhdGggY2xhc3M9InN0MCIgZD0iTTYsMTFWNyIvPgoJPHBhdGggY2xhc3M9InN0MCIgZD0iTTQsOWg0Ii8+CjwvZz4KPC9zdmc+";
    a[3] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNzUgNzUiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDc1IDc1OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6I0IxNjRBNTtzdHJva2Utd2lkdGg6NTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik00Nyw1OUgyOCBNMzcuNSw2OVY0Ni4yYy0xMC4xLDAtMTguMy04LjItMTguMi0xOC4zYzAtMTAuMSw4LjItMTguMywxOC4zLTE4LjJTNTUuOSwxNy44LDU1LjgsMjgKCWMwLDEwLjEtOC4yLDE4LjItMTguMiwxOC4yIi8+Cjwvc3ZnPg==";
    a[4] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6I0ZGMDAwMDtzdHJva2Utd2lkdGg6MjtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0zMCwyMWMtNS4zLTQuMi0xMy0zLjMtMTcuMSwycy0zLjMsMTMsMiwxNy4xczEzLDMuMywxNy4xLTJjMy41LTQuNCwzLjUtMTAuNywwLTE1LjFsLTEtMWwxMS0xMUwzMCwyMXogTTMzLDExCgloOXY5Ii8+Cjwvc3ZnPg==";
    a[5] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6IzMzNjY5OTtzdHJva2Utd2lkdGg6MztzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0xNS45LDIwLjZjLTAuOSwwLTIuNy0wLjgtMi43LTQuMnMzLjYtNi44LDcuMy02LjhzNy4zLDIuNSw3LjMsOC41cy00LjUsMTUuMy0xMy42LDE1LjMgTTEzLjIsMzMuNGgyNi4zCgkgTTM0LjEsNDEuOHYtMzMiLz4KPC9zdmc+";
    a[6] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6Izk5NjY2NjtzdHJva2Utd2lkdGg6NDtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0xOS44LDUuOXYyOSBNMTQuOSwxMC43aDEyIE0zMy44LDQwLjljLTEsMS0yLDItMywycy0zLTEtMy0zczEtNCwzLTZzNC02LDQtMTBzLTItOC02LThjLTMuOCwwLTcsMi05LDYiLz4KPC9zdmc+";
    a[7] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzMzNjY2NjtzdHJva2U6IzMzNjY2NjtzdHJva2Utd2lkdGg6MC43NTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cgkuc3Qxe2ZpbGw6bm9uZTtzdHJva2U6IzMzNjY2NjtzdHJva2Utd2lkdGg6MztzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0xNC42LDMxLjZoLTd2LTFsNC0xdi0yMGwtNC0xdi0xaDdWMzEuNnogTTM2LjcsMzEuNmg3di0xbC00LTF2LTIwbDQtMXYtMWgtN1YzMS42eiIvPgo8cGF0aCBjbGFzcz0ic3QxIiBkPSJNMTMuNiwxOS42aDI0IE0yNS43LDcuNnYyNyBNMjUuNiwzNC42Yy0yLjIsMC00LDEuOC00LDRjMCwyLjIsMS44LDQsNCw0YzIuMiwwLDQtMS44LDQtNAoJQzI5LjYsMzYuNCwyNy45LDM0LjYsMjUuNiwzNC42TDI1LjYsMzQuNnoiLz4KPC9zdmc+";
    a[8] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6IzY2OTkzMztzdHJva2Utd2lkdGg6MztzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0xNS4xLDkuMWMtMi43LDE4LDEuOCwyMC43LDEwLjYsMjAuN1MzOSwyNy4yLDM2LjQsOS4xIE0yNS43LDEwLjl2MzMuNCBNMTguNywzNy4xaDE0LjIgTTEwLjIsMTEuNmw1LTMuOAoJbDMuNyw1LjEgTTIxLjIsMTUuOWw0LjQtNC42bDQuNSw0LjQgTTMyLjQsMTMuM2wzLjgtNS4xbDUsMy45Ii8+Cjwvc3ZnPg==";
    a[9] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkNhbHF1ZV8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNTAgNTAiIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDUwIDUwOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6I0ZGMzM2NjtzdHJva2Utd2lkdGg6MztzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0xNywzNi4xaDE2IE0yNSw0NC4xdi0xNyBNMTMsMTUuMWMwLDYuNiw1LjQsMTIsMTIsMTJzMTItNS40LDEyLTEyIE0yNSw4LjFjLTMuOSwwLTcsMy4xLTcsN2MwLDMuOSwzLjEsNyw3LDcKCWMzLjksMCw3LTMuMSw3LTdDMzIsMTEuMiwyOC45LDguMSwyNSw4LjFMMjUsOC4xeiIvPgo8L3N2Zz4=";
    a[10] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIKCSBpZD0ic3ZnOSIgaW5rc2NhcGU6dmVyc2lvbj0iMC45Mi41ICgyMDYwZWMxZjlmLCAyMDIwLTA0LTA4KSIgc29kaXBvZGk6ZG9jbmFtZT0iTWFycy5zdmciIHhtbG5zOmNjPSJodHRwOi8vY3JlYXRpdmVjb21tb25zLm9yZy9ucyMiIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6aW5rc2NhcGU9Imh0dHA6Ly93d3cuaW5rc2NhcGUub3JnL25hbWVzcGFjZXMvaW5rc2NhcGUiIHhtbG5zOnJkZj0iaHR0cDovL3d3dy53My5vcmcvMTk5OS8wMi8yMi1yZGYtc3ludGF4LW5zIyIgeG1sbnM6c29kaXBvZGk9Imh0dHA6Ly9zb2RpcG9kaS5zb3VyY2Vmb3JnZS5uZXQvRFREL3NvZGlwb2RpLTAuZHRkIiB4bWxuczpzdmc9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIgoJIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IiB2aWV3Qm94PSIwIDAgMTIgMTIiCgkgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTIgMTI7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojOTk5OTk5O3N0cm9rZS1taXRlcmxpbWl0OjEwO30KPC9zdHlsZT4KPHNvZGlwb2RpOm5hbWVkdmlldyAgYm9yZGVyY29sb3I9IiM2NjY2NjYiIGJvcmRlcm9wYWNpdHk9IjEiIGdyaWR0b2xlcmFuY2U9IjEwIiBndWlkZXRvbGVyYW5jZT0iMTAiIGlkPSJuYW1lZHZpZXcxMSIgaW5rc2NhcGU6Y3VycmVudC1sYXllcj0ic3ZnOSIgaW5rc2NhcGU6Y3g9IjMuOTEzMTYyNSIgaW5rc2NhcGU6Y3k9IjguMDMwNjgzMyIgaW5rc2NhcGU6cGFnZW9wYWNpdHk9IjAiIGlua3NjYXBlOnBhZ2VzaGFkb3c9IjIiIGlua3NjYXBlOnNuYXAtaW50ZXJzZWN0aW9uLXBhdGhzPSJ0cnVlIiBpbmtzY2FwZTpzbmFwLW1pZHBvaW50cz0idHJ1ZSIgaW5rc2NhcGU6c25hcC1vYmplY3QtbWlkcG9pbnRzPSJ0cnVlIiBpbmtzY2FwZTpzbmFwLXNtb290aC1ub2Rlcz0idHJ1ZSIgaW5rc2NhcGU6d2luZG93LWhlaWdodD0iMTAxNSIgaW5rc2NhcGU6d2luZG93LW1heGltaXplZD0iMSIgaW5rc2NhcGU6d2luZG93LXdpZHRoPSIxOTIwIiBpbmtzY2FwZTp3aW5kb3cteD0iMCIgaW5rc2NhcGU6d2luZG93LXk9IjAiIGlua3NjYXBlOnpvb209IjQxLjcxOTMiIG9iamVjdHRvbGVyYW5jZT0iMTAiIHBhZ2Vjb2xvcj0iI2ZmZmZmZiIgc2hvd2dyaWQ9ImZhbHNlIj4KCTwvc29kaXBvZGk6bmFtZWR2aWV3Pgo8ZyBpZD0iZzE0MTMiIHRyYW5zZm9ybT0icm90YXRlKC00NSw1LjIzMzQ4Myw1LjQyODI2MDgpIj4KCTxwYXRoIGlkPSJwYXRoMiIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgc29kaXBvZGk6bm9kZXR5cGVzPSJjc3NjIiBjbGFzcz0ic3QwIiBkPSJNNS43LDguM2MxLjQsMCwyLjYtMS4yLDIuNi0yLjYKCQlTNy4xLDMuMiw1LjcsMy4yUzMuMSw0LjQsMy4xLDUuOCIvPgoJPHBhdGggaWQ9InBhdGgyMyIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgY2xhc3M9InN0MCIgZD0iTTMuMSw1LjhDMy4xLDUuMywyLjcsNSwyLjMsNVMxLjUsNS4zLDEuNSw1LjhzMC40LDAuOCwwLjgsMC44CgkJUzMuMSw2LjIsMy4xLDUuOHoiLz4KCTxwYXRoIGlkPSJwYXRoMjMtMyIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgY2xhc3M9InN0MCIgZD0iTTYuNSw5LjJjMC0wLjQtMC40LTAuOC0wLjgtMC44UzQuOSw4LjcsNC45LDkuMQoJCWMwLDAuNCwwLjQsMC44LDAuOCwwLjhDNi4xLDkuOSw2LjUsOS42LDYuNSw5LjJ6Ii8+CjwvZz4KPC9zdmc+";
    a[11] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIKCSBpZD0ic3ZnMTMiIGlua3NjYXBlOnZlcnNpb249IjAuOTIuNSAoMjA2MGVjMWY5ZiwgMjAyMC0wNC0wOCkiIHNvZGlwb2RpOmRvY25hbWU9IlBob2x1c19zeW1ib2wuc3ZnIiB4bWxuczpjYz0iaHR0cDovL2NyZWF0aXZlY29tbW9ucy5vcmcvbnMjIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOmlua3NjYXBlPSJodHRwOi8vd3d3Lmlua3NjYXBlLm9yZy9uYW1lc3BhY2VzL2lua3NjYXBlIiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiIHhtbG5zOnNvZGlwb2RpPSJodHRwOi8vc29kaXBvZGkuc291cmNlZm9yZ2UubmV0L0RURC9zb2RpcG9kaS0wLmR0ZCIgeG1sbnM6c3ZnPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIKCSB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIgdmlld0JveD0iMCAwIDEyIDEyIgoJIHN0eWxlPSJlbmFibGUtYmFja2dyb3VuZDpuZXcgMCAwIDEyIDEyOyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6bm9uZTtzdHJva2U6Izk5OTk5OTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+Cjxzb2RpcG9kaTpuYW1lZHZpZXcgIGJvcmRlcmNvbG9yPSIjNjY2NjY2IiBib3JkZXJvcGFjaXR5PSIxIiBncmlkdG9sZXJhbmNlPSIxMCIgZ3VpZGV0b2xlcmFuY2U9IjEwIiBpZD0ibmFtZWR2aWV3MTUiIGlua3NjYXBlOmN1cnJlbnQtbGF5ZXI9InN2ZzEzIiBpbmtzY2FwZTpjeD0iMTUuNjg1NDc4IiBpbmtzY2FwZTpjeT0iOC42ODc5NDE2IiBpbmtzY2FwZTpwYWdlb3BhY2l0eT0iMCIgaW5rc2NhcGU6cGFnZXNoYWRvdz0iMiIgaW5rc2NhcGU6d2luZG93LWhlaWdodD0iMTAxNSIgaW5rc2NhcGU6d2luZG93LW1heGltaXplZD0iMSIgaW5rc2NhcGU6d2luZG93LXdpZHRoPSIxOTIwIiBpbmtzY2FwZTp3aW5kb3cteD0iMCIgaW5rc2NhcGU6d2luZG93LXk9IjAiIGlua3NjYXBlOnpvb209IjI5LjUiIG9iamVjdHRvbGVyYW5jZT0iMTAiIHBhZ2Vjb2xvcj0iI2ZmZmZmZiIgc2hvd2dyaWQ9ImZhbHNlIj4KCTwvc29kaXBvZGk6bmFtZWR2aWV3Pgo8cGF0aCBpZD0icGF0aDIiIGlua3NjYXBlOmNvbm5lY3Rvci1jdXJ2YXR1cmU9IjAiIGNsYXNzPSJzdDAiIGQ9Ik04LDkuOGMwLTAuNy0wLjktMS4yLTItMS4yUzQsOS4xLDQsOS44UzQuOSwxMSw2LDExUzgsMTAuNCw4LDkuOAoJeiIvPgo8cGF0aCBpZD0icGF0aDQiIGlua3NjYXBlOmNvbm5lY3Rvci1jdXJ2YXR1cmU9IjAiIHNvZGlwb2RpOm5vZGV0eXBlcz0iY2MiIGNsYXNzPSJzdDAiIGQ9Ik02LDguNXYtNSIvPgo8cGF0aCBpZD0icGF0aDgxNSIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgc29kaXBvZGk6bm9kZXR5cGVzPSJjYyIgY2xhc3M9InN0MCIgZD0iTTYsMWwwLDIuNSIvPgo8cGF0aCBpZD0icGF0aDgxNS0zIiBpbmtzY2FwZTpjb25uZWN0b3ItY3VydmF0dXJlPSIwIiBzb2RpcG9kaTpub2RldHlwZXM9ImNjIiBjbGFzcz0ic3QwIiBkPSJNNy44LDUuMkw2LDMuNSIvPgo8cGF0aCBpZD0icGF0aDgxNS02IiBpbmtzY2FwZTpjb25uZWN0b3ItY3VydmF0dXJlPSIwIiBzb2RpcG9kaTpub2RldHlwZXM9ImNjIiBjbGFzcz0ic3QwIiBkPSJNNy43LDEuN0w2LDMuNSIvPgo8L3N2Zz4=";
    a[12] = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMywgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIKCSBpZD0ic3ZnOSIgaW5rc2NhcGU6dmVyc2lvbj0iMC45Mi41ICgyMDYwZWMxZjlmLCAyMDIwLTA0LTA4KSIgc29kaXBvZGk6ZG9jbmFtZT0iTWFycy5zdmciIHhtbG5zOmNjPSJodHRwOi8vY3JlYXRpdmVjb21tb25zLm9yZy9ucyMiIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6aW5rc2NhcGU9Imh0dHA6Ly93d3cuaW5rc2NhcGUub3JnL25hbWVzcGFjZXMvaW5rc2NhcGUiIHhtbG5zOnJkZj0iaHR0cDovL3d3dy53My5vcmcvMTk5OS8wMi8yMi1yZGYtc3ludGF4LW5zIyIgeG1sbnM6c29kaXBvZGk9Imh0dHA6Ly9zb2RpcG9kaS5zb3VyY2Vmb3JnZS5uZXQvRFREL3NvZGlwb2RpLTAuZHRkIiB4bWxuczpzdmc9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIgoJIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IiB2aWV3Qm94PSIwIDAgMTIgMTIiCgkgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTIgMTI7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDojOTk5OTk5O3N0cm9rZTojOTk5OTk5O3N0cm9rZS13aWR0aDowLjY7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO3N0cm9rZS1taXRlcmxpbWl0OjEwO30KCS5zdDF7ZmlsbDojOTk5OTk5O3N0cm9rZTojOTk5OTk5O3N0cm9rZS13aWR0aDowLjI0NTg7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO3N0cm9rZS1taXRlcmxpbWl0OjMuMjc2ODt9Cjwvc3R5bGU+Cjxzb2RpcG9kaTpuYW1lZHZpZXcgIGJvcmRlcmNvbG9yPSIjNjY2NjY2IiBib3JkZXJvcGFjaXR5PSIxIiBncmlkdG9sZXJhbmNlPSIxMCIgZ3VpZGV0b2xlcmFuY2U9IjEwIiBpZD0ibmFtZWR2aWV3MTEiIGlua3NjYXBlOmN1cnJlbnQtbGF5ZXI9InN2ZzkiIGlua3NjYXBlOmN4PSI0Ljg3ODEzOSIgaW5rc2NhcGU6Y3k9IjYuNDc4OTU1OSIgaW5rc2NhcGU6cGFnZW9wYWNpdHk9IjAiIGlua3NjYXBlOnBhZ2VzaGFkb3c9IjIiIGlua3NjYXBlOndpbmRvdy1oZWlnaHQ9IjEwMTUiIGlua3NjYXBlOndpbmRvdy1tYXhpbWl6ZWQ9IjEiIGlua3NjYXBlOndpbmRvdy13aWR0aD0iMTkyMCIgaW5rc2NhcGU6d2luZG93LXg9IjAiIGlua3NjYXBlOndpbmRvdy15PSIwIiBpbmtzY2FwZTp6b29tPSIyOC45NjkyODEiIG9iamVjdHRvbGVyYW5jZT0iMTAiIHBhZ2Vjb2xvcj0iI2ZmZmZmZiIgc2hvd2dyaWQ9ImZhbHNlIj4KCTwvc29kaXBvZGk6bmFtZWR2aWV3Pgo8ZyBpZD0iZzg3MyI+Cgk8cGF0aCBpZD0icGF0aDQtNyIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgc29kaXBvZGk6bm9kZXR5cGVzPSJjY3NjY2NzY2MiIGNsYXNzPSJzdDAiIGQ9Ik00LjQsNC4zCgkJYzAsMS40LDEuNCwyLjUsMy4yLDIuNWwwLDBDNy40LDYuNiw3LjMsNi41LDcuMiw2LjRDNi40LDUuOCw2LDUsNiw0LjNzMC41LTEuNywxLjItMi4yYzAuMS0wLjIsMC4zLTAuMywwLjQtMC4zCgkJQzUuOCwxLjgsNC40LDIuOCw0LjQsNC4zeiIvPgoJPGcgaWQ9Imc4NTQiIHRyYW5zZm9ybT0idHJhbnNsYXRlKDMuOTE1MjU0MiwyMi4xMTkxNDQpIj4KCQk8ZyBpZD0iZzg2NiIgdHJhbnNmb3JtPSJtYXRyaXgoMC44LDAsMCwwLjgsMC40MTY5NDkxNiwtMi42MjM3Mjg4KSI+CgkJCTxwYXRoIGlkPSJwYXRoNCIgaW5rc2NhcGU6Y29ubmVjdG9yLWN1cnZhdHVyZT0iMCIgY2xhc3M9InN0MSIgZD0iTTIuMS0xNS44djUiLz4KCQkJPHBhdGggaWQ9InBhdGg2IiBpbmtzY2FwZTpjb25uZWN0b3ItY3VydmF0dXJlPSIwIiBjbGFzcz0ic3QxIiBkPSJNLTAuNC0xMy4zaDUiLz4KCQk8L2c+Cgk8L2c+CjwvZz4KPC9zdmc+";
    a[13] = a[10]; // TODO noeud lunaire sud depuis projet Xcode
    string r = "data:image/svg+xml;base64,";
    switch (astre) {
        case soleil:
            return r + a[0];
        case lune:
            return r + a[1];
        case mercure:
            return r + a[2];
        case venus:
            return r + a[3];
        case mars:
            return r + a[4];
        case jupiter:
            return r + a[5];
        case saturn:
            return r + a[6];
        case uranus:
            return r + a[7];
        case neptune:
            return r + a[8];
        case pluto:
            return r + a[9];
        case noeud_lunaire:
            return r + a[10];
        case chiron:
            return r + a[11];
        case ceres:
            return r + a[12];
        case noeud_lunaire_sud:
            return r + a[13];
    }
}

string Astre::nom(Astres a) {
    switch (a) {
        case Astres::soleil:
            return "Soleil";
        case Astres::lune:
            return "Lune";
        case Astres::mercure:
            return "Mercure";
        case Astres::venus:
            return "Venus";
        case Astres::mars:
            return "Mars";
        case Astres::jupiter:
            return "Jupiter";
        case Astres::saturn:
            return "Saturn";
        case Astres::uranus:
            return "Uranus";
        case Astres::neptune:
            return "Neptune";
        case Astres::pluto:
            return "Pluton";
        case Astres::noeud_lunaire:
            return "Noeud lunaire";
        default:
            return "";
    }
}

string* Astre::sign_name_and_svg(CalcUt calcul_ut) {
    string* res = new string[2];
    int s = SIGNS_BELIER;
    for (int i = 1; i < 13; ++i) {
        s = i;
        double pos = (i - 1) * 30;
        if (pos > 360) {
            pos -= 360;
        }
        if (calcul_ut.longitude >= pos && calcul_ut.longitude <= pos + 30) {
            res[0] = Sign::nom(s);
            res[1] = Sign::read_svg(s);
            return res;
        }
    }
    res[0] = Sign::nom(s);
    res[1] = Sign::read_svg(s);
    return res;
}


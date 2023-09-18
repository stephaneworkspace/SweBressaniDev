//
// Created by Stéphane on 27.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

const char* ASPECT_ASSET_CONJUNCTION = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNy4yIDcuMiIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNy4yIDcuMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtmaWxsOm5vbmU7c3Ryb2tlOiNGRjAwMDA7c3Ryb2tlLXdpZHRoOjAuNTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGlkPSJwYXRoMTItMyIgY2xhc3M9InN0MCIgZD0iTTMuOCw1YzAtMC45LTAuNy0xLjctMS43LTEuN0MxLjIsMy40LDAuNSw0LjEsMC41LDVzMC43LDEuNywxLjcsMS43UzMuOCw1LjksMy44LDVMMy44LDV6Ii8+CjxwYXRoIGlkPSJwYXRoODYwIiBjbGFzcz0ic3QwIiBkPSJNMy4zLDMuOGwzLjUtMy41Ii8+Cjwvc3ZnPg==";
const char* ASPECT_ASSET_OPPOSITION = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgOSA5IiBzdHlsZT0iZW5hYmxlLWJhY2tncm91bmQ6bmV3IDAgMCA5IDk7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojRkYwMDAwO3N0cm9rZS13aWR0aDowLjU7c3Ryb2tlLW1pdGVybGltaXQ6MTA7fQo8L3N0eWxlPgo8cGF0aCBpZD0icGF0aDEyIiBjbGFzcz0ic3QwIiBkPSJNOC41LDIuMmMwLTAuOS0wLjctMS43LTEuNy0xLjdTNS4yLDEuMiw1LjIsMi4yYzAsMC45LDAuNywxLjcsMS43LDEuN1M4LjUsMy4xLDguNSwyLjJMOC41LDIuMnoiCgkvPgo8cGF0aCBpZD0icGF0aDEyLTMiIGNsYXNzPSJzdDAiIGQ9Ik0zLjgsNi44YzAtMC45LTAuNy0xLjctMS43LTEuN2MtMC45LDAtMS43LDAuNy0xLjcsMS43czAuNywxLjcsMS43LDEuN1MzLjgsNy44LDMuOCw2LjhMMy44LDYuOAoJeiIvPgo8cGF0aCBpZD0icGF0aDg2MCIgY2xhc3M9InN0MCIgZD0iTTMuMyw1LjdsMi4zLTIuMyIvPgo8L3N2Zz4=";
const char* ASPECT_ASSET_TRINE = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOmJsdWU7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzE3ODUiPjxnIGlkPSJnMTc3OSI+PHBhdGggaWQ9InBhdGg0LTMtNi01NiIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTFIMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS44NCkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjwvZz48L2c+PC9zdmc+";
const char* ASPECT_ASSET_SQUARE = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgMTEiPjxkZWZzPjxzdHlsZT4uY2xzLTF7ZmlsbDpub25lO3N0cm9rZTpyZWQ7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzExNzgiPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExVjEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03IiBjbGFzcz0iY2xzLTEiIGQ9Ik0xMSwxSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03LTMiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTFWMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMC41KSIvPjwvZz48L3N2Zz4=";
const char* ASPECT_ASSET_SEXTILE = "PHN2ZyBpZD0iQ2FscXVlXzEiIGRhdGEtbmFtZT0iQ2FscXVlIDEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgdmlld0JveD0iMCAwIDQ0IDQwLjc2Ij48ZGVmcz48c3R5bGU+LmNscy0xe3N0cm9rZTpibHVlO3N0cm9rZS13aWR0aDo1LjVweDt9PC9zdHlsZT48L2RlZnM+PHBhdGggY2xhc3M9ImNscy0xIiBkPSJNNDcsMjJIM00xNCwzLDM2LDQxTTM2LDMsMTQsNDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0zIC0xLjYyKSIvPjwvc3ZnPg==";
const char* ASPECT_ASSET_INCONJUNCTION = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMyIgY2xhc3M9InN0MCIgZD0iTTEwLjUsMy43aC0xMCIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0yNy05IiBjbGFzcz0ic3QwIiBkPSJNNS41LDMuN0w4LDguMSIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0xLTAiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsMy43TDMsOC4xIi8+CjwvZz4KPC9zdmc+";
const char* ASPECT_ASSET_SEQUISQUARE = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgNy42NyA5LjU4Ij48ZGVmcz48c3R5bGU+LmNscy0xe2ZpbGw6bm9uZTtzdHJva2U6IzMwNjtzdHJva2UtbGluZWNhcDpyb3VuZDtzdHJva2UtbGluZWpvaW46cm91bmQ7fTwvc3R5bGU+PC9kZWZzPjxnIGlkPSJnMTg4OSI+PHBhdGggaWQ9InBhdGg0LTMtNi01NiIgY2xhc3M9ImNscy0xIiBkPSJNOS4zMyw4LjM0VjEuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTciIGNsYXNzPSJjbHMtMSIgZD0iTTkuMzMsMS42N0gyLjY3IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMi4xNyAtMS4xNykiLz48cGF0aCBpZD0icGF0aDQtMy03LTMiIGNsYXNzPSJjbHMtMSIgZD0iTTkuMzMsOC4zNEgyLjY3IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMi4xNyAtMS4xNykiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTIuNjcsOC4zNFYxLjY3IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMi4xNyAtMS4xNykiLz48L2c+PGcgaWQ9Imc0Nzg3Ij48cGF0aCBpZD0icGF0aDQtMy03LTMtNSIgY2xhc3M9ImNscy0xIiBkPSJNOC4xOSwxMC4yNUg0Ljg2IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMi4xNyAtMS4xNykiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTctMyIgY2xhc3M9ImNscy0xIiBkPSJNNC44NiwxMC4yNVY2IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMi4xNyAtMS4xNykiLz48L2c+PC9zdmc+";
const char* ASPECT_ASSET_SEMISQUARE = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOiMzMDY7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48cGF0aCBpZD0icGF0aDQtMy03LTMiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDEwLjMzSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTEuMTcpIi8+PHBhdGggaWQ9InBhdGg0LTMtNi01Ni03IiBjbGFzcz0iY2xzLTEiIGQ9Ik0xLDEwLjMzLDYsMS42NyIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS4xNykiLz48L3N2Zz4=";
const char* ASPECT_ASSET_SEMISEXTILE = "PCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMy0yIiBjbGFzcz0ic3QwIiBkPSJNMTAuNSw3LjdoLTEwIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTI3LTkiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsNy43TDgsMy4zIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTEtMCIgY2xhc3M9InN0MCIgZD0iTTUuNSw3LjdMMywzLjMiLz4KPC9nPgo8L3N2Zz4=";

// version cgi

const char* ASPECT_ASSET_CONJUNCTION_LIGHT = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNy4yIDcuMiIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNy4yIDcuMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtmaWxsOm5vbmU7c3Ryb2tlOiMwMDAwMDA7c3Ryb2tlLXdpZHRoOjAuNTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGlkPSJwYXRoMTItMyIgY2xhc3M9InN0MCIgZD0iTTMuOCw1YzAtMC45LTAuNy0xLjctMS43LTEuN0MxLjIsMy40LDAuNSw0LjEsMC41LDVzMC43LDEuNywxLjcsMS43UzMuOCw1LjksMy44LDVMMy44LDV6Ii8+CjxwYXRoIGlkPSJwYXRoODYwIiBjbGFzcz0ic3QwIiBkPSJNMy4zLDMuOGwzLjUtMy41Ii8+Cjwvc3ZnPg==";
const char* ASPECT_ASSET_CONJUNCTION_DARK = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNy4yIDcuMiIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNy4yIDcuMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtmaWxsOm5vbmU7c3Ryb2tlOiNGRkZGRkY7c3Ryb2tlLXdpZHRoOjAuNTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGlkPSJwYXRoMTItMyIgY2xhc3M9InN0MCIgZD0iTTMuOCw1YzAtMC45LTAuNy0xLjctMS43LTEuN0MxLjIsMy40LDAuNSw0LjEsMC41LDVzMC43LDEuNywxLjcsMS43UzMuOCw1LjksMy44LDVMMy44LDV6Ii8+CjxwYXRoIGlkPSJwYXRoODYwIiBjbGFzcz0ic3QwIiBkPSJNMy4zLDMuOGwzLjUtMy41Ii8+Cjwvc3ZnPg==";
const char* ASPECT_ASSET_OPPOSITION_LIGHT = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNy4yIDcuMiIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNy4yIDcuMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtmaWxsOm5vbmU7c3Ryb2tlOiNGRjAwMDA7c3Ryb2tlLXdpZHRoOjAuNTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGlkPSJwYXRoMTItMyIgY2xhc3M9InN0MCIgZD0iTTMuOCw1YzAtMC45LTAuNy0xLjctMS43LTEuN0MxLjIsMy40LDAuNSw0LjEsMC41LDVzMC43LDEuNywxLjcsMS43UzMuOCw1LjksMy44LDVMMy44LDV6Ii8+CjxwYXRoIGlkPSJwYXRoODYwIiBjbGFzcz0ic3QwIiBkPSJNMy4zLDMuOGwzLjUtMy41Ii8+Cjwvc3ZnPg==";
const char* ASPECT_ASSET_OPPOSITION_DARK = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzIzIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCIKCSB2aWV3Qm94PSIwIDAgNy4yIDcuMiIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNy4yIDcuMjsiIHhtbDpzcGFjZT0icHJlc2VydmUiPgo8c3R5bGUgdHlwZT0idGV4dC9jc3MiPgoJLnN0MHtmaWxsOm5vbmU7c3Ryb2tlOiNGRjAwMDA7c3Ryb2tlLXdpZHRoOjAuNTtzdHJva2UtbWl0ZXJsaW1pdDoxMDt9Cjwvc3R5bGU+CjxwYXRoIGlkPSJwYXRoMTItMyIgY2xhc3M9InN0MCIgZD0iTTMuOCw1YzAtMC45LTAuNy0xLjctMS43LTEuN0MxLjIsMy40LDAuNSw0LjEsMC41LDVzMC43LDEuNywxLjcsMS43UzMuOCw1LjksMy44LDVMMy44LDV6Ii8+CjxwYXRoIGlkPSJwYXRoODYwIiBjbGFzcz0ic3QwIiBkPSJNMy4zLDMuOGwzLjUtMy41Ii8+Cjwvc3ZnPg==";
const char* ASPECT_ASSET_TRINE_LIGHT = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOmJsdWU7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzE3ODUiPjxnIGlkPSJnMTc3OSI+PHBhdGggaWQ9InBhdGg0LTMtNi01NiIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTFIMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS44NCkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjwvZz48L2c+PC9zdmc+";
const char* ASPECT_ASSET_TRINE_DARK = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOiMwMDlGRkY7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzE3ODUiPjxnIGlkPSJnMTc3OSI+PHBhdGggaWQ9InBhdGg0LTMtNi01NiIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTFIMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS44NCkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTEsNiwyLjM0IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjg0KSIvPjwvZz48L2c+PC9zdmc+";
const char* ASPECT_ASSET_SQUARE_LIGHT = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgMTEiPjxkZWZzPjxzdHlsZT4uY2xzLTF7ZmlsbDpub25lO3N0cm9rZTpyZWQ7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzExNzgiPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExVjEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03IiBjbGFzcz0iY2xzLTEiIGQ9Ik0xMSwxSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03LTMiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTFWMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMC41KSIvPjwvZz48L3N2Zz4=";
const char* ASPECT_ASSET_SQUARE_DARK = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgMTEiPjxkZWZzPjxzdHlsZT4uY2xzLTF7ZmlsbDpub25lO3N0cm9rZTpyZWQ7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO308L3N0eWxlPjwvZGVmcz48ZyBpZD0iZzExNzgiPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExVjEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03IiBjbGFzcz0iY2xzLTEiIGQ9Ik0xMSwxSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy03LTMiIGNsYXNzPSJjbHMtMSIgZD0iTTExLDExSDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0wLjUgLTAuNSkiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTFWMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMC41KSIvPjwvZz48L3N2Zz4=";
const char* ASPECT_ASSET_SEXTILE_LIGHT = "PHN2ZyBpZD0iQ2FscXVlXzEiIGRhdGEtbmFtZT0iQ2FscXVlIDEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgdmlld0JveD0iMCAwIDQ0IDQwLjc2Ij48ZGVmcz48c3R5bGU+LmNscy0xe3N0cm9rZTpibHVlO3N0cm9rZS13aWR0aDo1LjVweDt9PC9zdHlsZT48L2RlZnM+PHBhdGggY2xhc3M9ImNscy0xIiBkPSJNNDcsMjJIM00xNCwzLDM2LDQxTTM2LDMsMTQsNDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0zIC0xLjYyKSIvPjwvc3ZnPg==";
const char* ASPECT_ASSET_SEXTILE_DARK = "PHN2ZyBpZD0iQ2FscXVlXzEiIGRhdGEtbmFtZT0iQ2FscXVlIDEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgdmlld0JveD0iMCAwIDQ0IDQwLjc2Ij48ZGVmcz48c3R5bGU+LmNscy0xe3N0cm9rZTojMDA5RkZGO3N0cm9rZS13aWR0aDo1LjVweDt9PC9zdHlsZT48L2RlZnM+PHBhdGggY2xhc3M9ImNscy0xIiBkPSJNNDcsMjJIM00xNCwzLDM2LDQxTTM2LDMsMTQsNDEiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0zIC0xLjYyKSIvPjwvc3ZnPg==";
const char* ASPECT_ASSET_INCONJUNCTION_LIGHT = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMyIgY2xhc3M9InN0MCIgZD0iTTEwLjUsMy43aC0xMCIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0yNy05IiBjbGFzcz0ic3QwIiBkPSJNNS41LDMuN0w4LDguMSIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0xLTAiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsMy43TDMsOC4xIi8+CjwvZz4KPC9zdmc+";
const char* ASPECT_ASSET_INCONJUNCTION_DARK = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMyIgY2xhc3M9InN0MCIgZD0iTTEwLjUsMy43aC0xMCIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0yNy05IiBjbGFzcz0ic3QwIiBkPSJNNS41LDMuN0w4LDguMSIvPgoJPHBhdGggaWQ9InBhdGg0LTMtNi0xLTAiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsMy43TDMsOC4xIi8+CjwvZz4KPC9zdmc+";
const char* ASPECT_ASSET_SEQUISQUARE_LIGHT = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgNy42NyA5LjU4Ij48ZGVmcz48c3R5bGU+LmNscy0xe2ZpbGw6bm9uZTtzdHJva2U6cmVkO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9PC9zdHlsZT48L2RlZnM+PGcgaWQ9ImcxODg5Ij48cGF0aCBpZD0icGF0aDQtMy02LTU2IiBjbGFzcz0iY2xzLTEiIGQ9Ik05LjMzLDguMzRWMS42NyIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTIuMTcgLTEuMTcpIi8+PHBhdGggaWQ9InBhdGg0LTMtNyIgY2xhc3M9ImNscy0xIiBkPSJNOS4zMywxLjY3SDIuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNOS4zMyw4LjM0SDIuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYtNyIgY2xhc3M9ImNscy0xIiBkPSJNMi42Nyw4LjM0VjEuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjwvZz48ZyBpZD0iZzQ3ODciPjxwYXRoIGlkPSJwYXRoNC0zLTctMy01IiBjbGFzcz0iY2xzLTEiIGQ9Ik04LjE5LDEwLjI1SDQuODYiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYtNy0zIiBjbGFzcz0iY2xzLTEiIGQ9Ik00Ljg2LDEwLjI1VjYiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjwvZz48L3N2Zz4=";
const char* ASPECT_ASSET_SEQUISQUARE_DARK = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgNy42NyA5LjU4Ij48ZGVmcz48c3R5bGU+LmNscy0xe2ZpbGw6bm9uZTtzdHJva2U6cmVkO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9PC9zdHlsZT48L2RlZnM+PGcgaWQ9ImcxODg5Ij48cGF0aCBpZD0icGF0aDQtMy02LTU2IiBjbGFzcz0iY2xzLTEiIGQ9Ik05LjMzLDguMzRWMS42NyIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTIuMTcgLTEuMTcpIi8+PHBhdGggaWQ9InBhdGg0LTMtNyIgY2xhc3M9ImNscy0xIiBkPSJNOS4zMywxLjY3SDIuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNOS4zMyw4LjM0SDIuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYtNyIgY2xhc3M9ImNscy0xIiBkPSJNMi42Nyw4LjM0VjEuNjciIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjwvZz48ZyBpZD0iZzQ3ODciPjxwYXRoIGlkPSJwYXRoNC0zLTctMy01IiBjbGFzcz0iY2xzLTEiIGQ9Ik04LjE5LDEwLjI1SDQuODYiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjxwYXRoIGlkPSJwYXRoNC0zLTYtNTYtNy0zIiBjbGFzcz0iY2xzLTEiIGQ9Ik00Ljg2LDEwLjI1VjYiIHRyYW5zZm9ybT0idHJhbnNsYXRlKC0yLjE3IC0xLjE3KSIvPjwvZz48L3N2Zz4=";
const char* ASPECT_ASSET_SEMISQUARE_LIGHT = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOnJlZDtzdHJva2UtbGluZWNhcDpyb3VuZDtzdHJva2UtbGluZWpvaW46cm91bmQ7fTwvc3R5bGU+PC9kZWZzPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTAuMzNIMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS4xNykiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTAuMzMsNiwxLjY3IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjE3KSIvPjwvc3ZnPg==";
const char* ASPECT_ASSET_SEMISQUARE_DARK = "PHN2ZyBpZD0ic3ZnOSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB2aWV3Qm94PSIwIDAgMTEgOS42NiI+PGRlZnM+PHN0eWxlPi5jbHMtMXtmaWxsOm5vbmU7c3Ryb2tlOnJlZDtzdHJva2UtbGluZWNhcDpyb3VuZDtzdHJva2UtbGluZWpvaW46cm91bmQ7fTwvc3R5bGU+PC9kZWZzPjxwYXRoIGlkPSJwYXRoNC0zLTctMyIgY2xhc3M9ImNscy0xIiBkPSJNMTEsMTAuMzNIMSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoLTAuNSAtMS4xNykiLz48cGF0aCBpZD0icGF0aDQtMy02LTU2LTciIGNsYXNzPSJjbHMtMSIgZD0iTTEsMTAuMzMsNiwxLjY3IiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMC41IC0xLjE3KSIvPjwvc3ZnPg==";
const char* ASPECT_ASSET_SEMISEXTILE_LIGHT = "PCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMy0yIiBjbGFzcz0ic3QwIiBkPSJNMTAuNSw3LjdoLTEwIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTI3LTkiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsNy43TDgsMy4zIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTEtMCIgY2xhc3M9InN0MCIgZD0iTTUuNSw3LjdMMywzLjMiLz4KPC9nPgo8L3N2Zz4=";
const char* ASPECT_ASSET_SEMISEXTILE_DARK = "PCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDI2LjAuMiwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPgo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9InN2ZzkiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4IgoJIHZpZXdCb3g9IjAgMCAxMSAxMSIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMTEgMTE7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4KPHN0eWxlIHR5cGU9InRleHQvY3NzIj4KCS5zdDB7ZmlsbDpub25lO3N0cm9rZTojMDA2NjMzO3N0cm9rZS1saW5lY2FwOnJvdW5kO3N0cm9rZS1saW5lam9pbjpyb3VuZDt9Cjwvc3R5bGU+CjxnIGlkPSJnMTEwMyI+Cgk8cGF0aCBpZD0icGF0aDQtMy0yIiBjbGFzcz0ic3QwIiBkPSJNMTAuNSw3LjdoLTEwIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTI3LTkiIGNsYXNzPSJzdDAiIGQ9Ik01LjUsNy43TDgsMy4zIi8+Cgk8cGF0aCBpZD0icGF0aDQtMy02LTEtMCIgY2xhc3M9InN0MCIgZD0iTTUuNSw3LjdMMywzLjMiLz4KPC9nPgo8L3N2Zz4=";

int* Aspect::angle(int a) {
    int* res = new int[2];
    switch (a) {
        case ASPECTS_CONJUNCTION:
            res[0] = 0;
            res[1] = 10;
            break;
        case ASPECTS_OPPOSITION:
            res[0] = 180;
            res[1] = 8;
            break;
        case ASPECTS_TRINE:
            res[0] = 120;
            res[1] = 7;
            break;
        case ASPECTS_SQUARE:
            res[0] = 90;
            res[1] = 6;
            break;
        case ASPECTS_SEXTILE:
            res[0] = 60;
            res[1] = 5;
            break;
        case ASPECTS_INCONJUNCTION:
            res[0] = 150;
            res[1] = 2;
            break;
        case ASPECTS_SEQUISQUARE:
            res[0] = 135;
            res[1] = 1;
            break;
        case ASPECTS_SEMISQUARE:
            res[0] = 45;
            res[1] = 1;
            break;
        case ASPECTS_SEMISEXTILE:
            res[0] = 30;
            res[1] = 1;
            break;
    }
    return res;
}

string Aspect::read_svg(int a) {
    string r = "data:image/svg+xml;base64,";
    switch (a) {
        case ASPECTS_CONJUNCTION:
            return r + ASPECT_ASSET_CONJUNCTION;
        case ASPECTS_OPPOSITION:
            return r + ASPECT_ASSET_OPPOSITION;
        case ASPECTS_TRINE:
            return r + ASPECT_ASSET_TRINE;
        case ASPECTS_SQUARE:
            return r + ASPECT_ASSET_SQUARE;
        case ASPECTS_SEXTILE:
            return r + ASPECT_ASSET_SEXTILE;
        case ASPECTS_INCONJUNCTION:
            return r + ASPECT_ASSET_INCONJUNCTION;
        case ASPECTS_SEQUISQUARE:
            return r + ASPECT_ASSET_SEQUISQUARE;
        case ASPECTS_SEMISQUARE:
            return r + ASPECT_ASSET_SEMISQUARE;
        case ASPECTS_SEMISEXTILE:
            return r + ASPECT_ASSET_SEMISEXTILE;
        default:
            return "";
    }
}

string Aspect::read_svg2(int a, int color_mode) {
    string r = "data:image/svg+xml;base64,";
    if (color_mode == COLOR_MODE_LIGHT) {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return r + ASPECT_ASSET_CONJUNCTION_LIGHT;
            case ASPECTS_OPPOSITION:
                return r + ASPECT_ASSET_OPPOSITION_LIGHT;
            case ASPECTS_TRINE:
                return r + ASPECT_ASSET_TRINE_LIGHT;
            case ASPECTS_SQUARE:
                return r + ASPECT_ASSET_SQUARE_LIGHT;
            case ASPECTS_SEXTILE:
                return r + ASPECT_ASSET_SEXTILE_LIGHT;
            case ASPECTS_INCONJUNCTION:
                return r + ASPECT_ASSET_INCONJUNCTION_LIGHT;
            case ASPECTS_SEQUISQUARE:
                return r + ASPECT_ASSET_SEQUISQUARE_LIGHT;
            case ASPECTS_SEMISQUARE:
                return r + ASPECT_ASSET_SEMISQUARE_LIGHT;
            case ASPECTS_SEMISEXTILE:
                return r + ASPECT_ASSET_SEMISEXTILE_LIGHT;
            default:
                return "";
        }
    } else {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return r + ASPECT_ASSET_CONJUNCTION_DARK;
            case ASPECTS_OPPOSITION:
                return r + ASPECT_ASSET_OPPOSITION_DARK;
            case ASPECTS_TRINE:
                return r + ASPECT_ASSET_TRINE_DARK;
            case ASPECTS_SQUARE:
                return r + ASPECT_ASSET_SQUARE_DARK;
            case ASPECTS_SEXTILE:
                return r + ASPECT_ASSET_SEXTILE_DARK;
            case ASPECTS_INCONJUNCTION:
                return r + ASPECT_ASSET_INCONJUNCTION_DARK;
            case ASPECTS_SEQUISQUARE:
                return r + ASPECT_ASSET_SEQUISQUARE_DARK;
            case ASPECTS_SEMISQUARE:
                return r + ASPECT_ASSET_SEMISQUARE_DARK;
            case ASPECTS_SEMISEXTILE:
                return r + ASPECT_ASSET_SEMISEXTILE_DARK;
            default:
                return "";
        }
    }
}

const char* Aspect::read_svg_c(int a) {
    switch (a) {
        case ASPECTS_CONJUNCTION:
            return ASPECT_ASSET_CONJUNCTION;
        case ASPECTS_OPPOSITION:
            return ASPECT_ASSET_OPPOSITION;
        case ASPECTS_TRINE:
            return ASPECT_ASSET_TRINE;
        case ASPECTS_SQUARE:
            return ASPECT_ASSET_SQUARE;
        case ASPECTS_SEXTILE:
            return ASPECT_ASSET_SEXTILE;
        case ASPECTS_INCONJUNCTION:
            return ASPECT_ASSET_INCONJUNCTION;
        case ASPECTS_SEQUISQUARE:
            return ASPECT_ASSET_SEQUISQUARE;
        case ASPECTS_SEMISQUARE:
            return ASPECT_ASSET_SEMISQUARE;
        case ASPECTS_SEMISEXTILE:
            return ASPECT_ASSET_SEMISEXTILE;
        default:
            return "";
    }
}

const char *Aspect::read_svg_c2(int a, int color_mode) {
    if (color_mode == COLOR_MODE_LIGHT) {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return ASPECT_ASSET_CONJUNCTION_LIGHT;
            case ASPECTS_OPPOSITION:
                return ASPECT_ASSET_OPPOSITION_LIGHT;
            case ASPECTS_TRINE:
                return ASPECT_ASSET_TRINE_LIGHT;
            case ASPECTS_SQUARE:
                return ASPECT_ASSET_SQUARE_LIGHT;
            case ASPECTS_SEXTILE:
                return ASPECT_ASSET_SEXTILE_LIGHT;
            case ASPECTS_INCONJUNCTION:
                return ASPECT_ASSET_INCONJUNCTION_LIGHT;
            case ASPECTS_SEQUISQUARE:
                return ASPECT_ASSET_SEQUISQUARE_LIGHT;
            case ASPECTS_SEMISQUARE:
                return ASPECT_ASSET_SEMISQUARE_LIGHT;
            case ASPECTS_SEMISEXTILE:
                return ASPECT_ASSET_SEMISEXTILE_LIGHT;
            default:
                return "";
        }
    } else {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return ASPECT_ASSET_CONJUNCTION_DARK;
            case ASPECTS_OPPOSITION:
                return ASPECT_ASSET_OPPOSITION_DARK;
            case ASPECTS_TRINE:
                return ASPECT_ASSET_TRINE_DARK;
            case ASPECTS_SQUARE:
                return ASPECT_ASSET_SQUARE_DARK;
            case ASPECTS_SEXTILE:
                return ASPECT_ASSET_SEXTILE_DARK;
            case ASPECTS_INCONJUNCTION:
                return ASPECT_ASSET_INCONJUNCTION_DARK;
            case ASPECTS_SEQUISQUARE:
                return ASPECT_ASSET_SEQUISQUARE_DARK;
            case ASPECTS_SEMISQUARE:
                return ASPECT_ASSET_SEMISQUARE_DARK;
            case ASPECTS_SEMISEXTILE:
                return ASPECT_ASSET_SEMISEXTILE_DARK;
            default:
                return "";
        }
    }
}

const char* Aspect::name(int a) {
    switch (a) {
        case ASPECTS_CONJUNCTION:
            return "Conjunction";
        case ASPECTS_OPPOSITION:
            return "Opposition";
        case ASPECTS_TRINE:
            return "Trine";
        case ASPECTS_SQUARE:
            return "Square";
        case ASPECTS_SEXTILE:
            return "Sextile";
        case ASPECTS_INCONJUNCTION:
            return "Inconjunction";
        case ASPECTS_SEQUISQUARE:
            return "Sequisquare";
        case ASPECTS_SEMISQUARE:
            return "Semisquare";
        case ASPECTS_SEMISEXTILE:
            return "Semisextile";
        default:
            return "";
    }
}

const char *Aspect::name_fr(int a) {
    switch (a) {
        case ASPECTS_CONJUNCTION:
            return "Conjonction";
        case ASPECTS_OPPOSITION:
            return "Opposition";
        case ASPECTS_TRINE:
            return "Trigone";
        case ASPECTS_SQUARE:
            return "Carré (quadrature)";
        case ASPECTS_SEXTILE:
            return "Sextile";
        case ASPECTS_INCONJUNCTION:
            return "Quinconce";
        case ASPECTS_SEQUISQUARE:
            return "Sequi-carré";
        case ASPECTS_SEMISQUARE:
            return "Semi-carré";
        case ASPECTS_SEMISEXTILE:
            return "Semi-sextile";
        default:
            return "";
    }
}

int Aspect::type_aspect(int a) {
    switch (a) {
        case ASPECTS_CONJUNCTION:
            return 0;
        case ASPECTS_OPPOSITION:
            return -2;
        case ASPECTS_TRINE:
            return 2;
        case ASPECTS_SQUARE:
            return -2;
        case ASPECTS_SEXTILE:
            return 2;
        case ASPECTS_INCONJUNCTION:
            return 0;
        case ASPECTS_SEQUISQUARE:
            return -1;
        case ASPECTS_SEMISQUARE:
            return -1;
        case ASPECTS_SEMISEXTILE:
            return 0;
        default:
            return 0;
    }
}

const char* Aspect::color2(int a, int color_mode) {
    if (color_mode == COLOR_MODE_LIGHT) {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return "#000000";
            case ASPECTS_OPPOSITION:
                return "#ff2700";
            case ASPECTS_TRINE:
                return "#0532ff";
            case ASPECTS_SQUARE:
                return "#ff2700";
            case ASPECTS_SEXTILE:
                return "#0532ff";
            case ASPECTS_INCONJUNCTION:
                return "#006633";
            case ASPECTS_SEQUISQUARE:
                return "#ff2700";
            case ASPECTS_SEMISQUARE:
                return "#ff2700";
            case ASPECTS_SEMISEXTILE:
                return "#006633";
            default:
                return "";
        }
    } else {
        switch (a) {
            case ASPECTS_CONJUNCTION:
                return "#ffffff";
            case ASPECTS_OPPOSITION:
                return "#ff2700";
            case ASPECTS_TRINE:
                return "#009fff;";
            case ASPECTS_SQUARE:
                return "#ff2700";
            case ASPECTS_SEXTILE:
                return "#009fff;";
            case ASPECTS_INCONJUNCTION:
                return "#006633";
            case ASPECTS_SEQUISQUARE:
                return "#ff2700";
            case ASPECTS_SEMISQUARE:
                return "#ff2700";
            case ASPECTS_SEMISEXTILE:
                return "#006633";
            default:
                return "";
        }
    }
}
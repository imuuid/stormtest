#pragma once

void driver();
bool checkstart();
int startServer();

inline int fDelay = 14;
inline int keyB = 82;
inline const char* html = R"(
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.6.0.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.0/css/all.min.css">
    <link href="https://raw.githubusercontent.com/stehack27/storm/main/Web/style.css" rel="stylesheet">
    <title> </title>
  </head>
  <body id="mainContainer">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"></script>
    <script src="https://raw.githubusercontent.com/stehack27/storm/main/Web/main.js"></script>
  </body>
</html>
)";

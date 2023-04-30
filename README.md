[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10831999&assignment_repo_type=AssignmentRepo)
# Project-CS180

# cs180-project-API-endpoints

**/createDB POST method**
-database name in body

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled.png)

-returns db id

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%201.png)

**/listDBs GET method**
-returns string with list of database IDs, string in json form

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%202.png)

**/createCollection GET method**
-body contains db_id and collectionName (names important)
-returns collectionID

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%203.png)

**/listCollection GET method**
-body with db_id
-returns collections in that DB, string in json form

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%204.png)

**/createDocument GET method**
-body with db_id and coll_id
-returns doc_id

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%205.png)

**/listDocuments GET method**
-body with db_id and coll_id
-returns string with list of document IDs

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%206.png)

**/updateDoctument/<int>/<int>/<int> POST method**
-call with db_id, coll_id, doc_id in URL, in that order
-json object in request body
-returns response of function(should just be 0)

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%207.png)

**/fetchDocument GET method**
-body with db_id, coll_id, doc_id 
-returns document contents, string in json form

![Untitled](cs180-project-API-endpoints%204e21289435f34ef2a6f88fad8519279f/Untitled%208.png)

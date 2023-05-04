import React, { useEffect } from 'react';
import axios from 'axios';

axios.get('http://54.183.24.168:4000/createCollection')
.then(response => {
  console.log(response.data);
})
.catch(error => {
  console.error(error);
});
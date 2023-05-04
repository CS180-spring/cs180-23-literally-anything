import React, { useEffect } from 'react';
import axios from 'axios';

export const listDBs = () => {
  axios.get('http://54.183.24.168:4000/listDBs').then(response => {
    console.log(response.data.content)
  })
  .catch(error => {
    console.log(error)
  })
}
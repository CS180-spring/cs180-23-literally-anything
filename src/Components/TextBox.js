import React, { useState } from 'react';
import './TextBox.css'
import axios from 'axios';

export function TextBox() {
  const [userInput, setUserInput] = useState('');

  const handleInputChange = (event) => {
    setUserInput(event.target.value);
  };


  const handleSubmit = () => {
    axios.post('https://54.177.181.151:4000/createDB', userInput)
    .then((response) => {
    console.log(response.data);
    })
    .catch((error) => {
    console.error(error);
    });
    console.log(userInput);
  };

  return (
    <div>
      <input type="text" value={userInput} onChange={handleInputChange} />
      <button onClick={handleSubmit}>Submit</button>
      {/* other JSX code */}
    </div>
  );
}
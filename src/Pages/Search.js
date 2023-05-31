import React, { useState, useEffect } from "react";
import axios from "axios";
import { useNavigate, Link, useLocation } from 'react-router-dom';

const Search = ({ object }) => {
    const [text, setText] = useState(JSON.stringify(object, null, 2));
    const navigate = useNavigate();
    const location = useLocation();

    return (
        <div className='Search'>
            <div className='container'>
    
            <div className="left-collumn">
                <h1>ReactDB</h1>
            </div>
    
            <div className='main_content'>
              <div className="edit_container">
                <textarea value={text} onChange={handleChange} rows={10} cols={50} />
                <button onClick={handleSave}>Save</button>
              </div>
            </div>
        
            </div>
        </div>
      );
}
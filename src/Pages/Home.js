import Header from '../Components/Header'
import React from 'react';
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import CreateDataBase from './CreateDataBase';

export default function Home() {
    const navigate = useNavigate();
    const redirectToCreateDataBase = () => {
        navigate("/CreateDataBase");
    };

    return (
        <>
        
            <Header />
            <h2> Home Page </h2>
            <hr />
            <button
                onClick={redirectToCreateDataBase}
                style={{ backgroundColor: "blue", color: "white" }}
                > Create Database 
            </button>
            <Routes>
                <Route path="/CreateDataBase" element={<CreateDataBase />} />
            </Routes>

        </>
    )
}

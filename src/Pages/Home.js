import Header from '../Components/Header'
import React from 'react';
import ViewDataBase from './ViewDataBase';
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import CreateDataBase from './CreateDataBase';

export default function Home() {
    const navigate = useNavigate();
    const redirectToCreateDataBase = () => {
        navigate("/CreateDataBase");
    };
    const redirectToViewDataBase = () => {
        navigate("/ViewDataBase");
    }


    return (
        <div className="container">
            <div className="sidebar">
                
            </div>


            <div className="main-content">
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
                <button
                    onClick={redirectToViewDataBase}
                    style={{ backgroundColor: "blue", color: "white" }}
                > View Database 
                </button>
                <Routes>
                    <Route path="/ViewDataBase" element={<ViewDataBase />} />
                </Routes>
            </div>
        </div>
    )
}
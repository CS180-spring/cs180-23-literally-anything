import Header from '../Components/Header'
import "./Home.css"
import { useLayoutEffect, React, useState } from 'react';
import ViewDataBase from './ViewDataBase';
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import CreateDataBase from './CreateDataBase';
import { Button } from '../Components/Button';



export default function Home() {
    const [button, setButton] = useState(true);
    const navigate = useNavigate();
    const redirectToCreateDataBase = () => {
        navigate("/CreateDataBase");
    }
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
                <Link to='/CreateDataBase' className='CreateDataBase'>
                    {button && <Button buttonStyle='btn--primary'> View Data Base
                    </Button>}
                </Link>
                <Routes>
                    <Route path="/CreateDataBase" element={<CreateDataBase />} />
                </Routes>
                <Link to='/ViewDataBase' className='ViewDataBase'>
                    {button && <Button buttonStyle='btn--primary'> View Data Base
                    </Button>}
                </Link>
                
                <Routes>
                    <Route path="/ViewDataBase" element={<ViewDataBase />} />
                </Routes>
            </div>
        </div>
    )
}